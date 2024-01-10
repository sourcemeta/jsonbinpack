#include "commands.h"
#include "defaults.h"
#include "resolver.h"

#include <sourcemeta/jsonbinpack/canonicalizer.h>
#include <sourcemeta/jsonbinpack/mapper.h>
#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

#include <cstdlib>    // EXIT_SUCCESS
#include <filesystem> // std::filesystem
#include <iostream>   // std::cin, std::cout, std::endl

static auto compile_from_json(sourcemeta::jsontoolkit::JSON &schema) -> int {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer;
  sourcemeta::jsonbinpack::Mapper mapper;

  canonicalizer.apply(schema, sourcemeta::jsontoolkit::default_schema_walker,
                      sourcemeta::jsonbinpack::cli::resolver,
                      sourcemeta::jsonbinpack::DEFAULT_METASCHEMA);
  mapper.apply(schema, sourcemeta::jsontoolkit::default_schema_walker,
               sourcemeta::jsonbinpack::cli::resolver,
               sourcemeta::jsonbinpack::DEFAULT_METASCHEMA);

  sourcemeta::jsontoolkit::prettify(schema, std::cout);
  std::cout << std::endl;
  return EXIT_SUCCESS;
}

auto sourcemeta::jsonbinpack::cli::compile(
    const std::filesystem::path &schema_path) -> int {
  auto schema = sourcemeta::jsontoolkit::from_file(schema_path);
  return compile_from_json(schema);
}

auto sourcemeta::jsonbinpack::cli::compile() -> int {
  sourcemeta::jsontoolkit::JSON schema =
      sourcemeta::jsontoolkit::parse(std::cin);
  return compile_from_json(schema);
}
