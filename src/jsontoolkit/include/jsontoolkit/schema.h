#ifndef SOURCEMETA_JSONTOOLKIT_SCHEMA_H_
#define SOURCEMETA_JSONTOOLKIT_SCHEMA_H_

#include <jsontoolkit/json.h>
#include <jsontoolkit/jsonschema/drafts/2020-12.h>
#include <string> // std::string

namespace sourcemeta::jsontoolkit::schema {

template <typename T>
auto is_schema(const sourcemeta::jsontoolkit::JSON<T> &document) -> bool {
  // A schema object MUST include a "$schema" attribute.
  // We don't want to play the game of attempting to guess
  // what version of the specification and vocabularies
  // are being loaded by a given schema.
  if (document.is_object() &&
      document.defines(sourcemeta::jsontoolkit::schema::draft2020_12::keywords::
                           core::schema) &&
      document
          .at(sourcemeta::jsontoolkit::schema::draft2020_12::keywords::core::
                  schema)
          .is_string()) {
    return true;
  }

  return document.is_boolean();
}

// TODO: Properly implement this function. For now, its just a stub
// that will always return true given a non-empty string.
// Later, it should check the meta-schema, check which vocabularies
// it includes, etc.
template <typename T>
auto has_vocabulary(const sourcemeta::jsontoolkit::JSON<T> &document,
                    const std::string &uri) -> bool {
  return (document.is_object() || document.is_boolean()) && !uri.empty();
}
} // namespace sourcemeta::jsontoolkit::schema

#endif
