#ifndef SOURCEMETA_JSONBINPACK_CANONICALIZER_UTILS_H_
#define SOURCEMETA_JSONBINPACK_CANONICALIZER_UTILS_H_

#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

#include <algorithm> // std::sort, std::unique, std::all_of
#include <set>       // std::set
#include <string>    // std::string

namespace sourcemeta::jsonbinpack::canonicalizer {

// We don't have to check for "type: boolean" as that type
// is collapsed to an enum by other canonicalizer rules.
auto is_boolean_schema(const sourcemeta::jsontoolkit::JSON &schema,
                       const std::set<std::string> &vocabularies) -> bool {
  // If it is an enumeration of booleans
  return vocabularies.contains(
             "https://json-schema.org/draft/2020-12/vocab/validation") &&
         schema.is_object() && schema.defines("enum") &&
         schema.at("enum").is_array() &&
         std::all_of(schema.at("enum").as_array().cbegin(),
                     schema.at("enum").as_array().cend(),
                     [](const auto &element) { return element.is_boolean(); });
}

// We don't have to check for "type: null" as that type
// is collapsed to an enum by other canonicalizer rules.
auto is_null_schema(const sourcemeta::jsontoolkit::JSON &schema,
                    const std::set<std::string> &vocabularies) -> bool {
  // If it is an enumeration of nulls
  return vocabularies.contains(
             "https://json-schema.org/draft/2020-12/vocab/validation") &&
         schema.is_object() && schema.defines("enum") &&
         schema.at("enum").is_array() &&
         std::all_of(schema.at("enum").as_array().cbegin(),
                     schema.at("enum").as_array().cend(),
                     [](const auto &element) { return element.is_null(); });
}

auto is_unique(const sourcemeta::jsontoolkit::JSON &document) -> bool {
  auto copy = document;
  std::sort(copy.as_array().begin(), copy.as_array().end());
  return std::unique(copy.as_array().begin(), copy.as_array().end()) ==
         copy.as_array().end();
}

} // namespace sourcemeta::jsonbinpack::canonicalizer

#endif
