#include <alterschema/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

#include <map> // std::map

namespace sourcemeta::jsonbinpack::canonicalizer {

class EmptyObjectAsConst final
    : public sourcemeta::alterschema::Rule<std::string> {
public:
  EmptyObjectAsConst() : Rule("empty_object_as_const"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           schema.is_object() && schema.defines(keywords::validation::type) &&
           schema.at(keywords::validation::type) == "object" &&
           schema.defines(keywords::validation::maxProperties) &&
           schema.at(keywords::validation::maxProperties).is_integer() &&
           schema.at(keywords::validation::maxProperties) == 0;
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    schema.assign(
        "const",
        std::map<std::string, sourcemeta::jsontoolkit::JSON<std::string>>{});
    schema.erase(keywords::validation::maxProperties);
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
