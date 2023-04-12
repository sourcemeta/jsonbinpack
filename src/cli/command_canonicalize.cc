#include "commands.h"
#include "defaults.h"
#include "resolver.h"

#include <jsonbinpack/canonicalizer/canonicalizer.h>
#include <jsontoolkit/json.h>

#include <cstdlib>    // EXIT_SUCCESS
#include <filesystem> // std::filesystem
#include <fstream>    // std::ifstream
#include <ios>        // std::ios_base
#include <iostream>   // std::cin, std::cout, std::endl;

static auto canonicalize_from_json(sourcemeta::jsontoolkit::JSON &schema)
    -> int {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{
      sourcemeta::jsonbinpack::cli::Resolver{}};
  canonicalizer.apply(schema, sourcemeta::jsonbinpack::DEFAULT_METASCHEMA);
  sourcemeta::jsontoolkit::prettify(schema, std::cout);
  std::cout << std::endl;
  return EXIT_SUCCESS;
}

auto sourcemeta::jsonbinpack::cli::canonicalize(
    const std::filesystem::path &schema_path) -> int {
  std::ifstream stream{schema_path};
  stream.exceptions(std::ios_base::badbit);
  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(stream)};
  return canonicalize_from_json(schema);
}

auto sourcemeta::jsonbinpack::cli::canonicalize() -> int {
  sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(std::cin)};
  return canonicalize_from_json(schema);
}
