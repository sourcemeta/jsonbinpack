class EqualNumericBoundsAsConst final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  EqualNumericBoundsAsConst()
      : SchemaTransformRule("equal_numeric_bounds_as_const") {};

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
           (schema.at("type").to_string() == "integer" ||
            schema.at("type").to_string() == "number") &&
           schema.defines("minimum") && schema.at("minimum").is_number() &&
           schema.defines("maximum") && schema.at("maximum").is_number() &&
           schema.at("minimum") == schema.at("maximum");
  }

  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.assign("const", transformer.schema().at("minimum"));
    transformer.erase("minimum");
    transformer.erase("maximum");
  }
};
