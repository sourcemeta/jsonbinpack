#include <sourcemeta/jsonbinpack/compiler.h>
#include <sourcemeta/jsonbinpack/runtime.h>

#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

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
  const sourcemeta::jsontoolkit::JSON instance =
      sourcemeta::jsontoolkit::from_file(instance_path);
  const std::filesystem::path directory{argv[2]};
  assert(std::filesystem::is_directory(directory));

  // Schema
  const std::filesystem::path schema_path{directory / "schema.json"};
  assert(std::filesystem::is_regular_file(schema_path));
  sourcemeta::jsontoolkit::JSON schema =
      sourcemeta::jsontoolkit::from_file(schema_path);

  // Canonicalize
  sourcemeta::jsonbinpack::canonicalize(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver, DEFAULT_METASCHEMA);

  std::ofstream canonical_output_stream(directory / "canonical.json",
                                        std::ios::binary);
  canonical_output_stream.exceptions(std::ios_base::badbit);
  sourcemeta::jsontoolkit::prettify(schema, canonical_output_stream);
  canonical_output_stream << "\n";
  canonical_output_stream.flush();
  canonical_output_stream.close();

  // Plan
  sourcemeta::jsonbinpack::plan(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver, DEFAULT_METASCHEMA);

  std::ofstream plan_output_stream(directory / "plan.json", std::ios::binary);
  plan_output_stream.exceptions(std::ios_base::badbit);
  sourcemeta::jsontoolkit::prettify(schema, plan_output_stream);
  plan_output_stream << "\n";
  plan_output_stream.flush();
  plan_output_stream.close();

  // Encoder
  const sourcemeta::jsonbinpack::Plan plan{
      sourcemeta::jsonbinpack::parse(schema)};
  std::ofstream output_stream(directory / "output.bin", std::ios::binary);
  output_stream.exceptions(std::ios_base::badbit);
  sourcemeta::jsonbinpack::Encoder encoder{output_stream};
  encoder.encode(instance, plan);
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
  const sourcemeta::jsontoolkit::JSON result = decoder.decode(plan);

  // Report results
  if (result == instance) {
    return EXIT_SUCCESS;
  } else {
    std::cerr << "GOT:\n";
    sourcemeta::jsontoolkit::prettify(result, std::cerr);
    std::cerr << "\nEXPECTED:\n";
    sourcemeta::jsontoolkit::prettify(instance, std::cerr);
    std::cerr << "\n";
    return EXIT_FAILURE;
  }
}
