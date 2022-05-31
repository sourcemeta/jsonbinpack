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
      document.is_string(
          sourcemeta::jsontoolkit::Schema::keyword_core_schema)) {
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

auto sourcemeta::jsontoolkit::Schema::contains(const std::string &key) const
    -> bool {
  return this->schema.contains(key);
}

auto sourcemeta::jsontoolkit::Schema::at(
    const std::string &key) const & -> const sourcemeta::jsontoolkit::JSON & {
  return this->schema.at(key);
}

auto sourcemeta::jsontoolkit::Schema::is_object() const -> bool {
  return this->schema.is_object();
}

auto sourcemeta::jsontoolkit::Schema::is_array(const std::string &key) const
    -> bool {
  return this->schema.is_array(key);
}

auto sourcemeta::jsontoolkit::Schema::is_string(const std::string &key) const
    -> bool {
  return this->schema.is_string(key);
}

auto sourcemeta::jsontoolkit::Schema::is_boolean(const std::string &key) const
    -> bool {
  return this->schema.is_boolean(key);
}

auto sourcemeta::jsontoolkit::Schema::is_integer(const std::string &key) const
    -> bool {
  return this->schema.is_integer(key);
}

auto sourcemeta::jsontoolkit::Schema::to_object() const
    -> const sourcemeta::jsontoolkit::Object<sourcemeta::jsontoolkit::JSON,
                                             std::string> & {
  return this->schema.to_object();
}

auto sourcemeta::jsontoolkit::Schema::to_array() const
    -> const sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON,
                                            std::string> & {
  return this->schema.to_array();
}

auto sourcemeta::jsontoolkit::Schema::to_array(const std::string &key) const
    -> const sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON,
                                            std::string> & {
  return this->schema.to_array(key);
}

auto sourcemeta::jsontoolkit::Schema::to_boolean(const std::string &key) const
    -> bool {
  return this->schema.to_boolean(key);
}

auto sourcemeta::jsontoolkit::Schema::to_integer(const std::string &key) const
    -> std::int64_t {
  return this->schema.to_integer(key);
}

auto sourcemeta::jsontoolkit::Schema::size(const std::string &key) const
    -> std::size_t {
  return this->schema.size(key);
}

auto sourcemeta::jsontoolkit::Schema::empty(const std::string &key) const
    -> bool {
  return this->schema.empty(key);
}
