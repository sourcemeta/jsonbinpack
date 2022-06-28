#include <alterschema/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>
#include <map> // std::map

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class ImplicitObjectProperties final
    : public sourcemeta::alterschema::Rule<std::string> {
public:
  ImplicitObjectProperties() : Rule("implicit_object_properties"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::applicator) &&
           schema.is_object() && schema.defines(keywords::validation::type) &&
           schema.at(keywords::validation::type) == "object" &&
           !schema.defines(keywords::applicator::properties);
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    std::map<std::string, sourcemeta::jsontoolkit::JSON<std::string>>
        properties{};
    schema.assign(keywords::applicator::properties, std::move(properties));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
