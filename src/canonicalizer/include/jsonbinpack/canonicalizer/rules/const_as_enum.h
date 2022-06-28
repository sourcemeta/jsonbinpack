#include <alterschema/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

#include <vector> // std::vector

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class ConstAsEnum final : public sourcemeta::alterschema::Rule {
public:
  ConstAsEnum() : Rule("const_as_enum"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           schema.is_object() && schema.defines(keywords::validation::_const);
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    schema.assign(keywords::validation::_enum,
                  std::vector<sourcemeta::jsontoolkit::JSON<std::string>>{
                      schema.at(keywords::validation::_const)});
    schema.erase(keywords::validation::_const);
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
