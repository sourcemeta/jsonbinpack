#include "commands.h"
#include "defaults.h"
#include "resolver.h"

#include <jsonbinpack/canonicalizer/canonicalizer.h>
#include <jsonbinpack/encoder/encoder.h>
#include <jsonbinpack/mapper/mapper.h>
#include <jsonbinpack/parser/parser.h>

#include <jsontoolkit/json.h>

#include <cstdlib>    // EXIT_SUCCESS
#include <filesystem> // std::filesystem
#include <fstream>    // std::ifstream
#include <ios>        // std::ios_base
#include <iostream>   // std::cin, std::cout

static auto encode_from_json(sourcemeta::jsontoolkit::JSON &schema,
                             const sourcemeta::jsontoolkit::JSON &instance)
    -> int {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{
      sourcemeta::jsonbinpack::cli::resolver};
  canonicalizer.apply(schema, sourcemeta::jsonbinpack::DEFAULT_METASCHEMA);
  sourcemeta::jsonbinpack::Mapper mapper{
      sourcemeta::jsonbinpack::cli::resolver};
  mapper.apply(schema, sourcemeta::jsonbinpack::DEFAULT_METASCHEMA);
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
  sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(schema_stream)};
  return encode_from_json(schema,
                          sourcemeta::jsontoolkit::parse(instance_stream));
}

auto sourcemeta::jsonbinpack::cli::encode(
    const std::filesystem::path &schema_path) -> int {
  std::ifstream schema_stream{schema_path};
  schema_stream.exceptions(std::ios_base::badbit);
  sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(schema_stream)};
  return encode_from_json(schema, sourcemeta::jsontoolkit::parse(std::cin));
}
