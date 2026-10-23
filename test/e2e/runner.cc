#include <sourcemeta/jsonbinpack/compiler.h>
#include <sourcemeta/jsonbinpack/runtime.h>

#include <sourcemeta/core/io.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>
#include <sourcemeta/core/options.h>

#include <algorithm>   // std::min
#include <cassert>     // assert
#include <cstdint>     // std::int64_t
#include <cstdlib>     // EXIT_SUCCESS, EXIT_FAILURE
#include <filesystem>  // std::filesystem
#include <iostream>    // std::cerr
#include <sstream>     // std::istringstream, std::ostringstream
#include <string>      // std::string, std::stoull, std::to_string
#include <string_view> // std::string_view

constexpr auto DEFAULT_METASCHEMA =
    "https://json-schema.org/draft/2020-12/schema";

namespace {

auto prettify_to_string(const sourcemeta::core::JSON &document) -> std::string {
  std::ostringstream stream;
  sourcemeta::core::prettify(document, stream);
  stream << "\n";
  return stream.str();
}

auto report_missing_artifact(const std::filesystem::path &path) -> void {
  std::cerr << "The artifact does not exist: " << path.string() << "\n";
}

auto report_artifact_mismatch(const std::filesystem::path &path) -> void {
  std::cerr << "The artifact does not match: " << path.string() << "\n";
}

auto first_difference(const std::string_view left, const std::string_view right)
    -> std::string_view::size_type {
  const auto bound{std::min(left.size(), right.size())};
  for (std::string_view::size_type index{0}; index < bound; index++) {
    if (left[index] != right[index]) {
      return index;
    }
  }

  return bound;
}

auto check_text_artifact(const std::filesystem::path &path,
                         const std::string_view actual) -> bool {
  if (!std::filesystem::is_regular_file(path)) {
    report_missing_artifact(path);
    return false;
  }

  const auto expected{sourcemeta::core::read_file_to_string(path)};
  if (expected == actual) {
    return true;
  }

  report_artifact_mismatch(path);
  std::cerr << "GOT:\n" << actual << "EXPECTED:\n" << expected;
  return false;
}

auto check_binary_artifact(const std::filesystem::path &path,
                           const std::string_view actual) -> bool {
  if (!std::filesystem::is_regular_file(path)) {
    report_missing_artifact(path);
    return false;
  }

  const auto expected{sourcemeta::core::read_file_to_string(path)};
  if (expected == actual) {
    return true;
  }

  report_artifact_mismatch(path);
  std::cerr << "GOT: " << actual.size() << " bytes\n"
            << "EXPECTED: " << expected.size() << " bytes\n"
            << "FIRST DIFFERENCE AT BYTE: "
            << first_difference(actual, expected) << "\n";
  return false;
}

auto check_size_artifact(const std::filesystem::path &path,
                         const std::string::size_type actual) -> bool {
  if (!std::filesystem::is_regular_file(path)) {
    report_missing_artifact(path);
    return false;
  }

  const auto expected{static_cast<std::string::size_type>(
      std::stoull(sourcemeta::core::read_file_to_string(path)))};
  if (expected == actual) {
    return true;
  }

  const auto difference{static_cast<std::int64_t>(actual) -
                        static_cast<std::int64_t>(expected)};
  report_artifact_mismatch(path);
  std::cerr << "GOT: " << actual << " bytes\n"
            << "EXPECTED: " << expected << " bytes\n"
            << "DIFFERENCE: " << (difference > 0 ? "+" : "") << difference
            << " bytes\n";
  return false;
}

} // namespace

auto main(int argc, char *argv[]) -> int {
  sourcemeta::core::Options application;
  application.flag("write", {"w"});
  application.parse(argc, argv);

  if (application.positional().size() < 2) {
    std::cerr << "Usage: " << argv[0]
              << " <instance.json> <directory> [--write]\n";
    return EXIT_FAILURE;
  }

  const std::filesystem::path instance_path{application.positional().at(0)};
  assert(std::filesystem::is_regular_file(instance_path));
  const sourcemeta::core::JSON instance =
      sourcemeta::core::read_json(instance_path);
  const std::filesystem::path directory{application.positional().at(1)};
  assert(std::filesystem::is_directory(directory));

  // Schema
  const std::filesystem::path schema_path{directory / "schema.json"};
  assert(std::filesystem::is_regular_file(schema_path));
  sourcemeta::core::JSON schema = sourcemeta::core::read_json(schema_path);

  // Canonicalize
  sourcemeta::jsonbinpack::canonicalize(schema, sourcemeta::core::schema_walker,
                                        sourcemeta::core::schema_resolver,
                                        DEFAULT_METASCHEMA);

  const sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::Locations, schema,
      sourcemeta::core::schema_walker, sourcemeta::core::schema_resolver,
      DEFAULT_METASCHEMA};
  sourcemeta::core::schema_format(schema, frame);
  const auto canonical{prettify_to_string(schema)};

  // Compile
  sourcemeta::jsonbinpack::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   DEFAULT_METASCHEMA);

  const auto encoding_document{prettify_to_string(schema)};

  // Encoder
  const sourcemeta::jsonbinpack::Encoding encoding{
      sourcemeta::jsonbinpack::load(schema)};
  std::ostringstream output_stream;
  sourcemeta::jsonbinpack::Encoder encoder{output_stream};
  encoder.write(instance, encoding);
  const auto output{output_stream.str()};

  // Decoder
  std::istringstream data_stream{output};
  sourcemeta::jsonbinpack::Decoder decoder{data_stream};
  const sourcemeta::core::JSON result = decoder.read(encoding);

  if (result != instance) {
    std::cerr << "GOT:\n";
    sourcemeta::core::prettify(result, std::cerr);
    std::cerr << "\nEXPECTED:\n";
    sourcemeta::core::prettify(instance, std::cerr);
    std::cerr << "\n";
    return EXIT_FAILURE;
  }

  const std::filesystem::path canonical_path{directory / "canonical.json"};
  const std::filesystem::path encoding_path{directory / "encoding.json"};
  const std::filesystem::path output_path{directory / "output.bin"};
  const std::filesystem::path size_path{directory / "size.txt"};

  if (application.contains("write")) {
    sourcemeta::core::write_file(canonical_path, canonical);
    sourcemeta::core::write_file(encoding_path, encoding_document);
    sourcemeta::core::write_file(output_path, output);
    sourcemeta::core::write_file(size_path,
                                 std::to_string(output.size()) + "\n");
    return EXIT_SUCCESS;
  }

  auto matches{check_text_artifact(canonical_path, canonical)};
  matches = check_text_artifact(encoding_path, encoding_document) && matches;
  matches = check_binary_artifact(output_path, output) && matches;
  matches = check_size_artifact(size_path, output.size()) && matches;

  if (!matches) {
    std::cerr << "\nIf these changes are expected, re-run as follows to "
                 "update the artifacts:\n  "
              << argv[0] << " " << instance_path.string() << " "
              << directory.string() << " --write\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
