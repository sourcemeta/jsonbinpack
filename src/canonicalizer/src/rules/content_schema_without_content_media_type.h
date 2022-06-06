#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class ContentSchemaWithoutContentMediaType final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  ContentSchemaWithoutContentMediaType()
      : Rule("content_schema_without_content_media_type"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, "https://json-schema.org/draft/2020-12/vocab/content") &&
           schema.is_object() && schema.contains("contentSchema") &&
           !schema.contains("contentMediaType");
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema)
      -> void override {
    schema.erase("contentSchema");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
