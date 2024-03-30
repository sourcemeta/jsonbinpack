class ImplicitUnitMultipleOf final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  ImplicitUnitMultipleOf() : SchemaTransformRule("implicit_unit_multiple_of"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON &schema,
            const std::string &dialect,
            const std::set<std::string> &vocabularies,
            const sourcemeta::jsontoolkit::Pointer &) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.defines("type") &&
           schema.at("type").is_string() &&
           schema.at("type").to_string() == "integer" &&
           !schema.defines("multipleOf");
  }

  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.assign("multipleOf", sourcemeta::jsontoolkit::JSON{1});
  }
};
