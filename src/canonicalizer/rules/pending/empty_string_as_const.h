#include <alterschema/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

#include <string> // std::string

namespace sourcemeta::jsonbinpack::canonicalizer {

class EmptyStringAsConst final
    : public sourcemeta::alterschema::Rule<std::string> {
public:
  EmptyStringAsConst() : Rule("empty_string_as_const"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           schema.is_object() && schema.defines(keywords::validation::type) &&
           schema.at(keywords::validation::type) == "string" &&
           schema.defines(keywords::validation::maxLength) &&
           schema.at(keywords::validation::maxLength).is_integer() &&
           schema.at(keywords::validation::maxLength) == 0;
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    schema.assign(keywords::validation::_const, std::string{});
    schema.erase(keywords::validation::maxLength);
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
