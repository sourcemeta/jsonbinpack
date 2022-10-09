#include <alterschema/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::mapper {

class IntegerLowerBound final
    : public sourcemeta::alterschema::Rule<std::string> {
public:
  IntegerLowerBound() : Rule("integer_lower_bound"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           schema.defines(keywords::validation::type) &&
           schema.at(keywords::validation::type) == "integer" &&
           schema.defines(keywords::validation::minimum) &&
           !schema.defines(keywords::validation::maximum) &&
           !schema.defines(keywords::validation::multipleOf);
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    const auto minimum = schema.at(keywords::validation::minimum).to_integer();
    return make_integer_encoding(schema, "FLOOR_MULTIPLE_ENUM_VARINT",
                                 {{"minimum", minimum}, {"multiplier", 1}});
  }
};

} // namespace sourcemeta::jsonbinpack::mapper
