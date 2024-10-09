#include <sourcemeta/jsonbinpack/compiler.h>
#include <sourcemeta/jsonbinpack/runtime.h>

#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

#include <cstdlib>  // EXIT_SUCCESS
#include <iostream> // std::cout

auto main() -> int {
  sourcemeta::jsontoolkit::JSON schema = sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": -100,
    "maximum": 100
  })JSON");

  sourcemeta::jsonbinpack::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver);

  const sourcemeta::jsonbinpack::Encoding encoding{
      sourcemeta::jsonbinpack::load(schema)};
  sourcemeta::jsonbinpack::Encoder encoder{std::cout};

  const sourcemeta::jsontoolkit::JSON instance{5};
  encoder.write(instance, encoding);

  std::cout << std::endl;
  return EXIT_SUCCESS;
}
