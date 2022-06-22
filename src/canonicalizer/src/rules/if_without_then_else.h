#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class IfWithoutThenElse final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  IfWithoutThenElse() : Rule("if_without_then_else"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::applicator) &&
           schema.is_object() && schema.defines(keywords::applicator::_if) &&
           !schema.defines(keywords::applicator::then) &&
           !schema.defines(keywords::applicator::_else);
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    schema.erase(keywords::applicator::_if);
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
