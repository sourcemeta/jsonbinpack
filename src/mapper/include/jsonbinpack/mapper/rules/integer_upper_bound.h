#include <alterschema/rule.h>
#include <jsonbinpack/mapper/format.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::mapper {

class IntegerUpperBound final
    : public sourcemeta::alterschema::Rule<std::string> {
public:
  IntegerUpperBound() : Rule("integer_upper_bound"){};

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
           schema.defines(keywords::validation::maximum) &&
           !schema.defines(keywords::validation::multipleOf);
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    const auto maximum = schema.at(keywords::validation::maximum).to_integer();
    return make_integer_encoding(schema, "ROOF_MULTIPLE_MIRROR_ENUM_VARINT",
                                 {{"maximum", maximum}, {"multiplier", 1}});
  }
};

} // namespace sourcemeta::jsonbinpack::mapper
