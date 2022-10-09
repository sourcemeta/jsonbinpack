#include <alterschema/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::mapper {

class IntegerUpperBoundMultiplier final
    : public sourcemeta::alterschema::Rule<std::string> {
public:
  IntegerUpperBoundMultiplier() : Rule("integer_upper_bound_multiplier"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           schema.defines(keywords::validation::type) &&
           schema.at(keywords::validation::type) == "integer" &&
           !schema.defines(keywords::validation::minimum) &&
           schema.defines(keywords::validation::maximum) &&
           schema.defines(keywords::validation::multipleOf) &&
           schema.at(keywords::validation::multipleOf).is_integer();
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    const auto maximum = schema.at(keywords::validation::maximum).to_integer();
    const auto multiplier =
        schema.at(keywords::validation::multipleOf).to_integer();
    return make_integer_encoding(
        schema, "ROOF_MULTIPLE_MIRROR_ENUM_VARINT",
        {{"maximum", maximum}, {"multiplier", multiplier}});
  }
};

} // namespace sourcemeta::jsonbinpack::mapper
