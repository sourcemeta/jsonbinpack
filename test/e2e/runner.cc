#include <sourcemeta/jsonbinpack/compiler.h>
#include <sourcemeta/jsonbinpack/runtime.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <cassert>    // assert
#include <cstdlib>    // EXIT_SUCCESS, EXIT_FAILURE
#include <filesystem> // std::filesystem
#include <fstream>    // std::ifstream, std::ofstream
#include <ios>        // std::ios_base, std::ios::binary
#include <iostream>   // std::cerr
#include <string>     // std::to_string

constexpr auto DEFAULT_METASCHEMA =
    "https://json-schema.org/draft/2020-12/schema";

auto main(int argc, char *argv[]) -> int {
  if (argc <= 2) {
    std::cerr << "Usage: " << argv[0] << " <instance.json> <directory>\n";
    return EXIT_FAILURE;
  }

  const std::filesystem::path instance_path{argv[1]};
  assert(std::filesystem::is_regular_file(instance_path));
  const sourcemeta::core::JSON instance =
      sourcemeta::core::read_json(instance_path);
  const std::filesystem::path directory{argv[2]};
  assert(std::filesystem::is_directory(directory));

  // Schema
  const std::filesystem::path schema_path{directory / "schema.json"};
  assert(std::filesystem::is_regular_file(schema_path));
  sourcemeta::core::JSON schema = sourcemeta::core::read_json(schema_path);

  // Canonicalize
  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver, DEFAULT_METASCHEMA);

  std::ofstream canonical_output_stream(directory / "canonical.json",
                                        std::ios::binary);
  canonical_output_stream.exceptions(std::ios_base::badbit);
  sourcemeta::core::prettify(schema, canonical_output_stream,
                             sourcemeta::core::schema_format_compare);
  canonical_output_stream << "\n";
  canonical_output_stream.flush();
  canonical_output_stream.close();

  // Compile
  sourcemeta::jsonbinpack::compile(
      schema, sourcemeta::core::schema_official_walker,
      sourcemeta::core::schema_official_resolver, DEFAULT_METASCHEMA);

  std::ofstream encoding_output_stream(directory / "encoding.json",
                                       std::ios::binary);
  encoding_output_stream.exceptions(std::ios_base::badbit);
  sourcemeta::core::prettify(schema, encoding_output_stream,
                             sourcemeta::core::schema_format_compare);
  encoding_output_stream << "\n";
  encoding_output_stream.flush();
  encoding_output_stream.close();

  // Encoder
  const sourcemeta::jsonbinpack::Encoding encoding{
      sourcemeta::jsonbinpack::load(schema)};
  std::ofstream output_stream(directory / "output.bin", std::ios::binary);
  output_stream.exceptions(std::ios_base::badbit);
  sourcemeta::jsonbinpack::Encoder encoder{output_stream};
  encoder.write(instance, encoding);
  output_stream.flush();
  const auto size{output_stream.tellp()};
  output_stream.close();
  std::ofstream size_stream(directory / "size.txt", std::ios::binary);
  size_stream.exceptions(std::ios_base::badbit);
  size_stream << std::to_string(size) << "\n";
  size_stream.flush();
  size_stream.close();

  // Decoder
  std::ifstream data_stream{directory / "output.bin", std::ios::binary};
  data_stream.exceptions(std::ios_base::badbit);
  sourcemeta::jsonbinpack::Decoder decoder{data_stream};
  const sourcemeta::core::JSON result = decoder.read(encoding);

  // Report results
  if (result == instance) {
    return EXIT_SUCCESS;
  } else {
    std::cerr << "GOT:\n";
    sourcemeta::core::prettify(result, std::cerr);
    std::cerr << "\nEXPECTED:\n";
    sourcemeta::core::prettify(instance, std::cerr);
    std::cerr << "\n";
    return EXIT_FAILURE;
  }
}
