#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>
#include <utility> // std::move
#include <vector>  // std::vector

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class TypeUnionAnyOf final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  TypeUnionAnyOf() : Rule("type_union_anyof"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema,
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema,
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           schema.is_object() && schema.defines("type") &&
           schema.at("type").is_array();
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    std::vector<sourcemeta::jsontoolkit::JSON<std::string>> disjunctors;
    for (const auto &type : schema.at("type").to_array()) {
      sourcemeta::jsontoolkit::JSON<std::string> disjunctor{schema};
      disjunctor.erase("$schema");
      disjunctor.assign("type", type);
      disjunctors.push_back(std::move(disjunctor));
    }

    if (schema.defines("$schema")) {
      sourcemeta::jsontoolkit::JSON<std::string> metaschema{
          schema.at("$schema")};
      schema.clear();
      schema.assign("$schema", std::move(metaschema));
    } else {
      schema.clear();
    }

    schema.assign("anyOf", std::move(disjunctors));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
