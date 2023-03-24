#include <alterschema/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::canonicalizer {

class DuplicateAnyOfBranches final
    : public sourcemeta::alterschema::Rule<std::string> {
public:
  DuplicateAnyOfBranches() : Rule("duplicate_anyof_branches"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    if (!sourcemeta::jsontoolkit::schema::has_vocabulary(
            schema, vocabularies::applicator) ||
        !schema.is_object() || !schema.defines(keywords::applicator::anyOf) ||
        !schema.at(keywords::applicator::anyOf).is_array()) {
      return false;
    }

    auto copy{schema.at(keywords::applicator::anyOf).to_array()};
    std::sort(std::begin(copy), std::end(copy));
    return std::unique(std::begin(copy), std::end(copy)) != std::end(copy);
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    auto &array = schema.at(keywords::applicator::anyOf).to_array();
    std::sort(std::begin(array), std::end(array));
    auto last = std::unique(std::begin(array), std::end(array));
    schema.at(keywords::applicator::anyOf).erase(last, std::end(array));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
