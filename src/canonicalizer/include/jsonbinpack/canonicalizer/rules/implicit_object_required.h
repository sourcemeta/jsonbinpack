#include <alterschema/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class ImplicitObjectRequired final
    : public sourcemeta::alterschema::Rule<std::string> {
public:
  ImplicitObjectRequired() : Rule("implicit_object_required"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           schema.is_object() && schema.defines(keywords::validation::type) &&
           schema.at(keywords::validation::type) == "object" &&
           !schema.defines(keywords::validation::required);
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    std::vector<sourcemeta::jsontoolkit::JSON<std::string>> required{};
    schema.assign(keywords::validation::required, std::move(required));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
