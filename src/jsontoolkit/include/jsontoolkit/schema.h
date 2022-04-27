#ifndef SOURCEMETA_JSONTOOLKIT_SCHEMA_H_
#define SOURCEMETA_JSONTOOLKIT_SCHEMA_H_

#include <jsontoolkit/json.h>
#include <memory>      // std::shared_ptr
#include <string>      // std::string
#include <string_view> // std::string_view

namespace sourcemeta::jsontoolkit {
/*
 * We model a JSON Schema document as containing a read-only JSON
 * (as schemas are expected to carry an "$id" and be immutable).
 */
class Schema {
public:
  Schema(const sourcemeta::jsontoolkit::JSON &);
  static auto is_schema(const sourcemeta::jsontoolkit::JSON &) -> bool;
  [[nodiscard]] auto has_vocabulary(const std::string &) const -> bool;
  [[nodiscard]] auto contains(const std::string_view &key) const -> bool;
  [[nodiscard]] auto
  operator[](const sourcemeta::jsontoolkit::Object::key_type &) const & -> const
      sourcemeta::jsontoolkit::JSON &;
  [[nodiscard]] auto is_object() const -> bool;
  [[nodiscard]] auto to_object() const
      -> std::shared_ptr<const sourcemeta::jsontoolkit::Object>;

  // https://json-schema.org/draft/2020-12/json-schema-core.html#rfc.section.8.1.1
  inline static const std::string keyword_core_schema = "$schema";

private:
  const sourcemeta::jsontoolkit::JSON &schema;
};
} // namespace sourcemeta::jsontoolkit

#endif
