#include <alterschema/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::canonicalizer {

class UnsatisfiableMaxContains final
    : public sourcemeta::alterschema::Rule<std::string> {
public:
  UnsatisfiableMaxContains() : Rule("unsatisfiable_max_contains"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           schema.is_object() &&
           schema.defines(keywords::validation::maxContains) &&
           schema.at(keywords::validation::maxContains).is_integer() &&
           schema.defines(keywords::validation::maxItems) &&
           schema.at(keywords::validation::maxItems).is_integer() &&
           schema.at(keywords::validation::maxContains).to_integer() >=
               schema.at(keywords::validation::maxItems).to_integer();
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    schema.erase(keywords::validation::maxContains);
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
