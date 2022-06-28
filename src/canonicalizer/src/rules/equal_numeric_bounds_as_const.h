#include <alterschema/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class EqualNumericBoundsAsConst final : public sourcemeta::alterschema::Rule {
public:
  EqualNumericBoundsAsConst() : Rule("equal_numeric_bounds_as_const"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           schema.is_object() &&
           schema.defines(keywords::validation::minimum) &&
           (schema.at(keywords::validation::minimum).is_integer() ||
            schema.at(keywords::validation::minimum).is_real()) &&
           schema.defines(keywords::validation::maximum) &&
           (schema.at(keywords::validation::maximum).is_integer() ||
            schema.at(keywords::validation::maximum).is_real());
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    schema.assign(keywords::validation::_const,
                  schema.at(keywords::validation::minimum));
    schema.erase(keywords::validation::minimum);
    schema.erase(keywords::validation::maximum);
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
