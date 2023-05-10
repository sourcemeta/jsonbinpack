#include "commands.h"
#include "defaults.h"

#include <jsonbinpack/mapper/mapper.h>
#include <jsontoolkit/json.h>

#include <cstdlib>    // EXIT_SUCCESS
#include <filesystem> // std::filesystem
#include <fstream>    // std::ifstream
#include <ios>        // std::ios_base
#include <iostream>   // std::cin, std::cout, std::endl

static auto compile_from_json(sourcemeta::jsontoolkit::JSON &schema) -> int {
  sourcemeta::jsonbinpack::Mapper mapper{
      sourcemeta::jsontoolkit::DefaultResolver{}};
  mapper.apply(schema, sourcemeta::jsonbinpack::DEFAULT_METASCHEMA);
  sourcemeta::jsontoolkit::prettify(schema, std::cout);
  std::cout << std::endl;
  return EXIT_SUCCESS;
}

auto sourcemeta::jsonbinpack::cli::compile(
    const std::filesystem::path &schema_path) -> int {
  std::ifstream stream{schema_path};
  stream.exceptions(std::ios_base::badbit);
  sourcemeta::jsontoolkit::JSON schema{sourcemeta::jsontoolkit::parse(stream)};
  return compile_from_json(schema);
}

auto sourcemeta::jsonbinpack::cli::compile() -> int {
  sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(std::cin)};
  return compile_from_json(schema);
}
