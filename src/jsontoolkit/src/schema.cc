#include <jsontoolkit/schema.h>
#include <stdexcept> // std::invalid_argument, std::logic_error

sourcemeta::jsontoolkit::Schema::Schema(
    const sourcemeta::jsontoolkit::JSON &document)
    : schema{document} {
  if (!sourcemeta::jsontoolkit::Schema::is_schema(this->schema)) {
    throw std::invalid_argument("Invalid schema");
  }
}

auto sourcemeta::jsontoolkit::Schema::is_schema(
    const sourcemeta::jsontoolkit::JSON &document) -> bool {
  // A schema object MUST include a "$schema" attribute.
  // We don't want to play the game of attempting to guess
  // what version of the specification and vocabularies
  // are being loaded by a given schema.
  if (document.is_object() &&
      document.contains(sourcemeta::jsontoolkit::Schema::keyword_core_schema) &&
      document[sourcemeta::jsontoolkit::Schema::keyword_core_schema]
          .is_string()) {
    return true;
  }

  return document.is_boolean();
}

// TODO: Properly implement this function. For now, its just a stub
// that will always return true given a non-empty string.
// Later, it should check the meta-schema, check which vocabularies
// it includes, etc.
auto sourcemeta::jsontoolkit::Schema::has_vocabulary(
    const std::string &uri) const -> bool {
  return (this->schema.is_object() || this->schema.is_array()) && !uri.empty();
}

auto sourcemeta::jsontoolkit::Schema::contains(
    const std::string_view &key) const -> bool {
  return this->schema.contains(key);
}

auto sourcemeta::jsontoolkit::Schema::operator[](const std::string_view &key)
    const & -> const sourcemeta::jsontoolkit::JSON & {
  return this->schema[key];
}

auto sourcemeta::jsontoolkit::Schema::is_object() const -> bool {
  return this->schema.is_object();
}

auto sourcemeta::jsontoolkit::Schema::to_object() const
    -> const sourcemeta::jsontoolkit::Object & {
  return this->schema.to_object();
}

auto sourcemeta::jsontoolkit::Schema::to_array() const
    -> const sourcemeta::jsontoolkit::Array & {
  return this->schema.to_array();
}
