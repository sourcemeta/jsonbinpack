#include "commands.h"
#include "defaults.h"

#include <sourcemeta/jsonbinpack/canonicalizer.h>
#include <sourcemeta/jsonbinpack/mapper.h>
#include <sourcemeta/jsonbinpack/parser.h>
#include <sourcemeta/jsonbinpack/runtime.h>

#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

#include <cstdlib>    // EXIT_SUCCESS
#include <filesystem> // std::filesystem
#include <iostream>   // std::cin, std::cout

static auto encode_from_json(sourcemeta::jsontoolkit::JSON &schema,
                             const sourcemeta::jsontoolkit::JSON &instance)
    -> int {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer;
  sourcemeta::jsonbinpack::Mapper mapper;

  canonicalizer.apply(schema, sourcemeta::jsontoolkit::default_schema_walker,
                      sourcemeta::jsontoolkit::official_resolver,
                      sourcemeta::jsonbinpack::DEFAULT_METASCHEMA);
  mapper.apply(schema, sourcemeta::jsontoolkit::default_schema_walker,
               sourcemeta::jsontoolkit::official_resolver,
               sourcemeta::jsonbinpack::DEFAULT_METASCHEMA);

  const sourcemeta::jsonbinpack::Encoding encoding{
      sourcemeta::jsonbinpack::parse(schema)};
  sourcemeta::jsonbinpack::Encoder encoder{std::cout};
  encoder.encode(instance, encoding);
  return EXIT_SUCCESS;
}

auto sourcemeta::jsonbinpack::cli::encode(
    const std::filesystem::path &schema_path,
    const std::filesystem::path &instance_path) -> int {
  auto schema = sourcemeta::jsontoolkit::from_file(schema_path);
  return encode_from_json(schema,
                          sourcemeta::jsontoolkit::from_file(instance_path));
}

auto sourcemeta::jsonbinpack::cli::encode(
    const std::filesystem::path &schema_path) -> int {
  auto schema = sourcemeta::jsontoolkit::from_file(schema_path);
  return encode_from_json(schema, sourcemeta::jsontoolkit::parse(std::cin));
}
