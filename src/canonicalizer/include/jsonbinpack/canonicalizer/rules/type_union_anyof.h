#include <alterschema/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

#include <utility> // std::move
#include <vector>  // std::vector

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class TypeUnionAnyOf final : public sourcemeta::alterschema::Rule<std::string> {
public:
  TypeUnionAnyOf() : Rule("type_union_anyof"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::applicator) &&
           schema.is_object() && schema.defines(keywords::validation::type) &&
           schema.at(keywords::validation::type).is_array();
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
    std::vector<sourcemeta::jsontoolkit::JSON<std::string>> disjunctors;
    for (const auto &type : schema.at(keywords::validation::type).to_array()) {
      sourcemeta::jsontoolkit::JSON<std::string> disjunctor{schema};
      disjunctor.erase(keywords::core::schema);
      disjunctor.assign(keywords::validation::type, type);
      disjunctors.push_back(std::move(disjunctor));
    }

    if (schema.defines(keywords::core::schema)) {
      sourcemeta::jsontoolkit::JSON<std::string> metaschema{
          schema.at(keywords::core::schema)};
      schema.clear();
      schema.assign(keywords::core::schema, std::move(metaschema));
    } else {
      schema.clear();
    }

    schema.assign(keywords::applicator::anyOf, std::move(disjunctors));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
