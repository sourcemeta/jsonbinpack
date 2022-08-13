#include <alterschema/rule.h>
#include <cstdint> // std::uint8_t
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>
#include <limits> // std::numeric_limits

namespace sourcemeta::jsonbinpack::mapper {

class IntegerBounded8Bit final
    : public sourcemeta::alterschema::Rule<std::string> {
public:
  IntegerBounded8Bit() : Rule("integer_bounded_8_bit"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           schema.defines(keywords::validation::type) &&
           schema.at(keywords::validation::type) == "integer" &&
           schema.defines(keywords::validation::minimum) &&
           schema.defines(keywords::validation::maximum) &&
           schema.at(keywords::validation::maximum).to_integer() -
                   schema.at(keywords::validation::minimum).to_integer() <=
               std::numeric_limits<std::uint8_t>::max() &&
           !schema.defines(keywords::validation::multipleOf);
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    const auto minimum = schema.at(keywords::validation::minimum).to_integer();
    const auto maximum = schema.at(keywords::validation::maximum).to_integer();
    return make_integer_encoding(
        schema, "BOUNDED_MULTIPLE_8BITS_ENUM_FIXED",
        {{"minimum", minimum}, {"maximum", maximum}, {"multiplier", 1}});
  }
};

} // namespace sourcemeta::jsonbinpack::mapper