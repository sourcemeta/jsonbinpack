class TypeUnionAnyOf final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  TypeUnionAnyOf() : SchemaTransformRule("type_union_anyof"){};

  [[nodiscard]] auto condition(const sourcemeta::jsontoolkit::JSON &schema,
                               const std::string &dialect,
                               const std::set<std::string> &vocabularies,
                               const sourcemeta::jsontoolkit::Pointer &) const
      -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           schema.is_object() && schema.defines("type") &&
           schema.at("type").is_array();
  }

  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    sourcemeta::jsontoolkit::JSON disjunctors =
        sourcemeta::jsontoolkit::JSON::make_array();
    for (const auto &type : transformer.schema().at("type").as_array()) {
      auto copy = transformer.schema();
      // TODO: Handle $id too and other top-level keywords that should not
      // remain
      copy.erase("$schema");
      copy.assign("type", type);
      disjunctors.push_back(std::move(copy));
    }

    sourcemeta::jsontoolkit::JSON result =
        sourcemeta::jsontoolkit::JSON::make_object();
    if (transformer.schema().defines("$schema")) {
      result.assign("$schema", transformer.schema().at("$schema"));
    }

    result.assign("anyOf", std::move(disjunctors));
    transformer.replace(std::move(result));
  }
};
