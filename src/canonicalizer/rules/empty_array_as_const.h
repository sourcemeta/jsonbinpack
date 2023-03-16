#include <alterschema/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

#include <vector> // std::vector

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class EmptyArrayAsConst final
    : public sourcemeta::alterschema::Rule<std::string> {
public:
  EmptyArrayAsConst() : Rule("empty_array_as_const"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           schema.is_object() && schema.defines(keywords::validation::type) &&
           schema.at(keywords::validation::type) == "array" &&
           schema.defines(keywords::validation::maxItems) &&
           schema.at(keywords::validation::maxItems).is_integer() &&
           schema.at(keywords::validation::maxItems) == 0;
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    schema.assign(keywords::validation::_const,
                  std::vector<sourcemeta::jsontoolkit::JSON<std::string>>{});
    schema.erase(keywords::validation::maxItems);
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
