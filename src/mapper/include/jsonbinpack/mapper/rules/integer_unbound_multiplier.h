#include <alterschema/rule.h>
#include <jsonbinpack/mapper/format.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::mapper {

class IntegerUnboundMultiplier final
    : public sourcemeta::alterschema::Rule<std::string> {
public:
  IntegerUnboundMultiplier() : Rule("integer_unbound_multiplier"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    return !schema.defines(format::encoding) &&
           sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           schema.defines(keywords::validation::type) &&
           schema.at(keywords::validation::type) == "integer" &&
           !schema.defines(keywords::validation::minimum) &&
           !schema.defines(keywords::validation::maximum) &&
           schema.defines(keywords::validation::multipleOf) &&
           schema.at(keywords::validation::multipleOf).is_integer();
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    const auto multiplier =
        schema.at(keywords::validation::multipleOf).to_integer();
    return make_integer_encoding(schema, "ARBITRARY_MULTIPLE_ZIGZAG_VARINT",
                                 {{"multiplier", multiplier}});
  }
};

} // namespace sourcemeta::jsonbinpack::mapper
