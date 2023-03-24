#ifndef SOURCEMETA_JSONBINPACK_CANONICALIZER_UTILS_H_
#define SOURCEMETA_JSONBINPACK_CANONICALIZER_UTILS_H_

#include <jsontoolkit/json.h>
#include <jsontoolkit/jsonschema.h>

#include <string>        // std::string
#include <unordered_map> // std::unordered_map

namespace sourcemeta::jsonbinpack::canonicalizer {

// We don't have to check for "type: boolean" as that type
// is collapsed to an enum by other canonicalizer rules.
auto is_boolean_schema(
    const sourcemeta::jsontoolkit::Value &schema,
    const std::unordered_map<std::string, bool> &vocabularies) -> bool {
  // If it is an enumeration of booleans
  return vocabularies.contains(
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
}

} // namespace sourcemeta::jsonbinpack::canonicalizer

#endif
