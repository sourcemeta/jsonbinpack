#include <jsonbinpack/canonicalizer/canonicalizer.h>
#include <jsonbinpack/decoder/decoder.h>
#include <jsonbinpack/encoder/encoder.h>
#include <jsonbinpack/mapper/mapper.h>
#include <jsonbinpack/parser/parser.h>
#include <jsontoolkit/json.h>

#include <cassert>    // assert
#include <cstdlib>    // EXIT_SUCCESS, EXIT_FAILURE
#include <filesystem> // std::filesystem
#include <fstream>    // std::ifstream, std::ofstream
#include <ios>        // std::ios_base
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
  std::ifstream instance_stream{instance_path};
  instance_stream.exceptions(std::ios_base::badbit);
  const sourcemeta::jsontoolkit::JSON instance{
      sourcemeta::jsontoolkit::parse(instance_stream)};
  const std::filesystem::path directory{argv[2]};
  assert(std::filesystem::is_directory(directory));
  const auto resolver{sourcemeta::jsontoolkit::DefaultResolver{}};

  // Schema
  const std::filesystem::path schema_path{directory / "schema.json"};
  assert(std::filesystem::is_regular_file(schema_path));
  std::ifstream schema_stream{schema_path};
  schema_stream.exceptions(std::ios_base::badbit);
  sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(schema_stream)};

  // Canonicalize
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{resolver};
  canonicalizer.apply(schema, DEFAULT_METASCHEMA);
  std::ofstream canonical_output_stream(directory / "canonical.json");
  canonical_output_stream.exceptions(std::ios_base::badbit);
  sourcemeta::jsontoolkit::prettify(schema, canonical_output_stream);
  canonical_output_stream << std::endl;
  canonical_output_stream.flush();
  canonical_output_stream.close();

  // Mapper
  sourcemeta::jsonbinpack::Mapper mapper{resolver};
  mapper.apply(schema, DEFAULT_METASCHEMA);
  std::ofstream mapper_output_stream(directory / "encoding.json");
  mapper_output_stream.exceptions(std::ios_base::badbit);
  sourcemeta::jsontoolkit::prettify(schema, mapper_output_stream);
  mapper_output_stream << std::endl;
  mapper_output_stream.flush();
  mapper_output_stream.close();

  // Encoder
  const sourcemeta::jsonbinpack::Encoding encoding{
      sourcemeta::jsonbinpack::parse(schema)};
  std::ofstream output_stream(directory / "output.bin");
  output_stream.exceptions(std::ios_base::badbit);
  sourcemeta::jsonbinpack::Encoder encoder{output_stream};
  encoder.encode(instance, encoding);
  output_stream.flush();
  const auto size{output_stream.tellp()};
  output_stream.close();
  std::ofstream size_stream(directory / "size.txt");
  size_stream.exceptions(std::ios_base::badbit);
  size_stream << std::to_string(size) << "\n";
  size_stream.flush();
  size_stream.close();

  // Decoder
  std::ifstream data_stream{directory / "output.bin"};
  data_stream.exceptions(std::ios_base::badbit);
  sourcemeta::jsonbinpack::Decoder decoder{data_stream};
  const sourcemeta::jsontoolkit::JSON result{decoder.decode(encoding)};

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
