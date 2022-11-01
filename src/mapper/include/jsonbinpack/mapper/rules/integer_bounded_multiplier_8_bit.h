#include <alterschema/rule.h>
#include <jsonbinpack/mapper/format.h>
#include <jsonbinpack/mapper/states/integer.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

#include <cstdint>  // std::uint8_t
#include <limits>   // std::numeric_limits
#include <optional> // std::optional

namespace sourcemeta::jsonbinpack::mapper {

class IntegerBoundedMultiplier8Bit final
    : public sourcemeta::alterschema::Rule<std::string> {
public:
  IntegerBoundedMultiplier8Bit() : Rule("integer_bounded_multiplier_8_bit"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    if (schema.defines(format::encoding) ||
        !sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
            schema, vocabularies::validation) ||
        !schema.defines(keywords::validation::type) ||
        !(schema.at(keywords::validation::type) == "integer") ||
        !schema.defines(keywords::validation::minimum) ||
        !schema.defines(keywords::validation::maximum) ||
        !schema.defines(keywords::validation::multipleOf) ||
        !schema.at(keywords::validation::multipleOf).is_integer()) {
      return false;
    }

    const std::optional<sourcemeta::jsontoolkit::JSON<std::string>> states{
        sourcemeta::jsonbinpack::mapper::states::integer(schema)};
    return states.has_value() &&
           states->size() <= std::numeric_limits<std::uint8_t>::max();
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    const auto minimum = schema.at(keywords::validation::minimum).to_integer();
    const auto maximum = schema.at(keywords::validation::maximum).to_integer();
    const auto multiplier =
        schema.at(keywords::validation::multipleOf).to_integer();
    return make_integer_encoding(schema, "BOUNDED_MULTIPLE_8BITS_ENUM_FIXED",
                                 {{"minimum", minimum},
                                  {"maximum", maximum},
                                  {"multiplier", multiplier}});
  }
};

} // namespace sourcemeta::jsonbinpack::mapper