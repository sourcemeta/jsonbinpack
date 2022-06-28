#include <alterschema/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class DuplicateAnyOfBranches final
    : public sourcemeta::alterschema::Rule<std::string> {
public:
  DuplicateAnyOfBranches() : Rule("duplicate_anyof_branches"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    if (!sourcemeta::jsontoolkit::schema::has_vocabulary(
            schema, vocabularies::applicator) ||
        !schema.is_object() || !schema.defines(keywords::applicator::anyOf) ||
        !schema.at(keywords::applicator::anyOf).is_array()) {
      return false;
    }

    sourcemeta::jsontoolkit::JSON<std::string> copy{
        schema.at(keywords::applicator::anyOf)};
    unique(copy);
    return schema.at(keywords::applicator::anyOf).size() > copy.size();
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    unique(schema.at(keywords::applicator::anyOf));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
