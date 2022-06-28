#include <algorithm> // std::all_of
#include <alterschema/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class ImpliedArrayUniqueItems final : public sourcemeta::alterschema::Rule {
public:
  ImpliedArrayUniqueItems() : Rule("implied_array_unique_items"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    const bool singular_by_max_items{
        schema.is_object() && schema.defines(keywords::validation::maxItems) &&
        schema.at(keywords::validation::maxItems).is_integer() &&
        schema.at(keywords::validation::maxItems).to_integer() <= 1};

    const bool singular_by_const{
        schema.is_object() && schema.defines(keywords::validation::_const) &&
        schema.at(keywords::validation::_const).is_array() &&
        schema.at(keywords::validation::_const).size() <= 1};

    const bool singular_by_enum{
        schema.is_object() && schema.defines(keywords::validation::_enum) &&
        schema.at(keywords::validation::_enum).is_array() &&
        std::all_of(
            schema.at(keywords::validation::_enum).to_array().cbegin(),
            schema.at(keywords::validation::_enum).to_array().cend(),
            [](const sourcemeta::jsontoolkit::JSON<std::string> &element) {
              return !element.is_array() || element.size() <= 1;
            })};

    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           schema.is_object() &&
           schema.defines(keywords::validation::uniqueItems) &&
           schema.at(keywords::validation::uniqueItems).is_boolean() &&
           schema.at(keywords::validation::uniqueItems).to_boolean() &&
           (singular_by_max_items || singular_by_const || singular_by_enum);
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    schema.erase(keywords::validation::uniqueItems);
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
