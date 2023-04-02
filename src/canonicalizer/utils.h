#ifndef SOURCEMETA_JSONBINPACK_CANONICALIZER_UTILS_H_
#define SOURCEMETA_JSONBINPACK_CANONICALIZER_UTILS_H_

#include <jsontoolkit/json.h>
#include <jsontoolkit/jsonschema.h>

#include <algorithm>     // std::sort, std::unique, std::all_of
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

// We don't have to check for "type: null" as that type
// is collapsed to an enum by other canonicalizer rules.
auto is_null_schema(const sourcemeta::jsontoolkit::Value &schema,
                    const std::unordered_map<std::string, bool> &vocabularies)
    -> bool {
  // If it is an enumeration of nulls
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
                       return sourcemeta::jsontoolkit::is_null(element);
                     });
}

auto is_unique(const sourcemeta::jsontoolkit::Value &document) -> bool {
  auto copy{sourcemeta::jsontoolkit::from(document)};
  std::sort(sourcemeta::jsontoolkit::begin_array(copy),
            sourcemeta::jsontoolkit::end_array(copy),
            sourcemeta::jsontoolkit::compare);
  return std::unique(sourcemeta::jsontoolkit::begin_array(copy),
                     sourcemeta::jsontoolkit::end_array(copy)) !=
         sourcemeta::jsontoolkit::end_array(copy);
}

} // namespace sourcemeta::jsonbinpack::canonicalizer

#endif
