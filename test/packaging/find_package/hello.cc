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
      sourcemeta::jsontoolkit::official_resolver,
      "https://json-schema.org/draft/2020-12/schema");

  const sourcemeta::jsonbinpack::Plan plan{
      sourcemeta::jsonbinpack::load(schema)};

  const sourcemeta::jsontoolkit::JSON instance{5};
  sourcemeta::jsonbinpack::Encoder encoder{std::cout};
  encoder.write(instance, plan);
  std::cout << std::endl;
  return EXIT_SUCCESS;
}
