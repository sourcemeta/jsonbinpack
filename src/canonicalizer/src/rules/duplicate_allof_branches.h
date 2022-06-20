#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/algorithm.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class DuplicateAllOfBranches final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  DuplicateAllOfBranches() : Rule("duplicate_allof_branches"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    if (!sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
            schema, "https://json-schema.org/draft/2020-12/vocab/applicator") ||
        !schema.is_object() || !schema.defines("allOf") ||
        !schema.at("allOf").is_array()) {
      return false;
    }

    sourcemeta::jsontoolkit::JSON<std::string> copy = schema.at("allOf");
    sourcemeta::jsontoolkit::unique(copy);
    return schema.at("allOf").size() > copy.size();
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    sourcemeta::jsontoolkit::unique(schema.at("allOf"));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
