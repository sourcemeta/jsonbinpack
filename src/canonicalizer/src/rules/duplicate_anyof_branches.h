#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/algorithm.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class DuplicateAnyOfBranches final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  DuplicateAnyOfBranches() : Rule("duplicate_anyof_branches"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    if (!sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
            schema, "https://json-schema.org/draft/2020-12/vocab/applicator") ||
        !schema.is_object() || !schema.defines("anyOf") ||
        !schema.at("anyOf").is_array()) {
      return false;
    }

    sourcemeta::jsontoolkit::JSON<std::string> copy = schema.at("anyOf");
    sourcemeta::jsontoolkit::unique(copy);
    return schema.at("anyOf").size() > copy.size();
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    sourcemeta::jsontoolkit::unique(schema.at("anyOf"));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
