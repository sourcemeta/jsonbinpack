#ifndef SOURCEMETA_JSONBINPACK_CANONICALIZER_UTILS_H_
#define SOURCEMETA_JSONBINPACK_CANONICALIZER_UTILS_H_

#include <jsontoolkit/json.h>
#include <jsontoolkit/jsonschema.h>

#include <string>        // std::string
#include <unordered_map> // std::unordered_map

namespace sourcemeta::jsonbinpack::canonicalizer {

auto is_boolean_schema(
    const sourcemeta::jsontoolkit::Value &schema,
    const std::unordered_map<std::string, bool> &vocabularies) -> bool {

  // If the "type" is set to "boolean" explicitly
  const bool is_boolean_type =
      vocabularies.contains(
          "https://json-schema.org/draft/2020-12/vocab/validation") &&
      sourcemeta::jsontoolkit::is_object(schema) &&
      sourcemeta::jsontoolkit::defines(schema, "type") &&
      sourcemeta::jsontoolkit::is_string(
          sourcemeta::jsontoolkit::at(schema, "type")) &&
      sourcemeta::jsontoolkit::to_string(
          sourcemeta::jsontoolkit::at(schema, "type")) == "boolean";

  // If it is an enumeration of booleans
  const bool is_boolean_enum =
      vocabularies.contains(
          "https://json-schema.org/draft/2020-12/vocab/validation") &&
      sourcemeta::jsontoolkit::is_object(schema) &&
      sourcemeta::jsontoolkit::defines(schema, "enum") &&
      sourcemeta::jsontoolkit::is_array(
          sourcemeta::jsontoolkit::at(schema, "enum")) &&
      std::all_of(sourcemeta::jsontoolkit::cbegin_array(
                      sourcemeta::jsontoolkit::at(schema, "enum")),
                  sourcemeta::jsontoolkit::cend_array(
                      sourcemeta::jsontoolkit::at(schema, "enum")),
                  [](const auto &element) {
                    return sourcemeta::jsontoolkit::is_boolean(element);
                  });

  return is_boolean_type || is_boolean_enum;
}

} // namespace sourcemeta::jsonbinpack::canonicalizer

#endif
