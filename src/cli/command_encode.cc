#include "commands.h"

#include <jsonbinpack/encoder/encoder.h>
#include <jsonbinpack/parser/parser.h>

#include <jsontoolkit/json.h>

#include <cstdlib>    // EXIT_SUCCESS
#include <filesystem> // std::filesystem
#include <fstream>    // std::ifstream
#include <ios>        // std::ios_base
#include <iostream>   // std::cin, std::cout

static auto encode_from_json(const sourcemeta::jsontoolkit::JSON &schema,
                             const sourcemeta::jsontoolkit::JSON &instance)
    -> int {
  // TODO: Run canonicalizer and mapper on the schema.
  // These components are vocabulary-aware, so they will
  // be a no-op if the schema is already an encoding schema.
  const sourcemeta::jsonbinpack::Encoding encoding{
      sourcemeta::jsonbinpack::parse(schema)};
  sourcemeta::jsonbinpack::Encoder encoder{std::cout};
  encoder.encode(instance, encoding);
  return EXIT_SUCCESS;
}

auto sourcemeta::jsonbinpack::cli::encode(
    const std::filesystem::path &schema_path,
    const std::filesystem::path &instance_path) -> int {
  std::ifstream schema_stream{schema_path};
  std::ifstream instance_stream{instance_path};
  schema_stream.exceptions(std::ios_base::badbit);
  instance_stream.exceptions(std::ios_base::badbit);
  return encode_from_json(sourcemeta::jsontoolkit::parse(schema_stream),
                          sourcemeta::jsontoolkit::parse(instance_stream));
}

auto sourcemeta::jsonbinpack::cli::encode(
    const std::filesystem::path &schema_path) -> int {
  std::ifstream schema_stream{schema_path};
  schema_stream.exceptions(std::ios_base::badbit);
  return encode_from_json(sourcemeta::jsontoolkit::parse(schema_stream),
                          sourcemeta::jsontoolkit::parse(std::cin));
}
