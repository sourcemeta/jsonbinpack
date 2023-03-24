namespace sourcemeta::jsonbinpack::canonicalizer {

class TypeUnionAnyOf final : public sourcemeta::alterschema::Rule {
public:
  TypeUnionAnyOf() : Rule("type_union_anyof"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::applicator) &&
           schema.is_object() && schema.defines(keywords::validation::type) &&
           schema.at(keywords::validation::type).is_array();
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
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

} // namespace sourcemeta::jsonbinpack::canonicalizer
