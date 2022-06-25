#include <jsonbinpack/canonicalizer/rule.h>
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
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    if (!sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
            schema, vocabularies::applicator) ||
        !schema.is_object() || !schema.defines(keywords::applicator::allOf) ||
        !schema.at(keywords::applicator::allOf).is_array()) {
      return false;
    }

    sourcemeta::jsontoolkit::JSON<std::string> copy{
        schema.at(keywords::applicator::allOf)};
    unique(copy);
    return schema.at(keywords::applicator::allOf).size() > copy.size();
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    unique(schema.at(keywords::applicator::allOf));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
