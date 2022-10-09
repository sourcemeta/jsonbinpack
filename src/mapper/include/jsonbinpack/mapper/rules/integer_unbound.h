#include <alterschema/rule.h>
#include <jsonbinpack/mapper/format.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::mapper {

class IntegerUnbound final : public sourcemeta::alterschema::Rule<std::string> {
public:
  IntegerUnbound() : Rule("integer_unbound"){};

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
           !schema.defines(keywords::validation::multipleOf);
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    return make_integer_encoding(schema, "ARBITRARY_MULTIPLE_ZIGZAG_VARINT",
                                 {{"multiplier", 1}});
  }
};

} // namespace sourcemeta::jsonbinpack::mapper
