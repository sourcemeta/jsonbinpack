#ifndef SOURCEMETA_JSONTOOLKIT_SCHEMA_H_
#define SOURCEMETA_JSONTOOLKIT_SCHEMA_H_

#include <jsontoolkit/json.h>
#include <memory> // std::shared_ptr
#include <string> // std::string

namespace sourcemeta::jsontoolkit {
/*
 * We model a JSON Schema document as containing a read-only JSON
 * (as schemas are expected to carry an "$id" and be immutable).
 */
class Schema {
public:
  Schema(const sourcemeta::jsontoolkit::JSON<std::string> &);
  static auto is_schema(const sourcemeta::jsontoolkit::JSON<std::string> &)
      -> bool;
  [[nodiscard]] auto has_vocabulary(const std::string &) const -> bool;
  [[nodiscard]] auto contains(const std::string &key) const -> bool;
  [[nodiscard]] auto at(const std::string &key) const & -> const
      sourcemeta::jsontoolkit::JSON<std::string> &;
  [[nodiscard]] auto is_object() const -> bool;
  [[nodiscard]] auto to_object() const -> const sourcemeta::jsontoolkit::Object<
      sourcemeta::jsontoolkit::JSON<std::string>, std::string> &;
  [[nodiscard]] auto to_array() const -> const sourcemeta::jsontoolkit::Array<
      sourcemeta::jsontoolkit::JSON<std::string>, std::string> &;
  [[nodiscard]] auto to_array(const std::string &key) const
      -> const sourcemeta::jsontoolkit::Array<
          sourcemeta::jsontoolkit::JSON<std::string>, std::string> &;
  [[nodiscard]] auto is_array(const std::string &key) const -> bool;
  [[nodiscard]] auto is_string(const std::string &key) const -> bool;
  [[nodiscard]] auto is_boolean(const std::string &key) const -> bool;
  [[nodiscard]] auto to_boolean(const std::string &key) const -> bool;
  [[nodiscard]] auto is_integer(const std::string &key) const -> bool;
  [[nodiscard]] auto to_integer(const std::string &key) const -> std::int64_t;
  [[nodiscard]] auto size(const std::string &key) const -> std::size_t;
  [[nodiscard]] auto empty(const std::string &key) const -> bool;

  // https://json-schema.org/draft/2020-12/json-schema-core.html#rfc.section.8.1.1
  inline static const std::string keyword_core_schema = "$schema";

private:
  const sourcemeta::jsontoolkit::JSON<std::string> &schema;
};
} // namespace sourcemeta::jsontoolkit

#endif
