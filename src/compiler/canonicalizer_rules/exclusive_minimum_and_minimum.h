class ExclusiveMinimumAndMinimum final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  ExclusiveMinimumAndMinimum()
      : SchemaTransformRule("exclusive_minimum_and_minimum") {};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON &schema,
            const std::string &dialect,
            const std::set<std::string> &vocabularies,
            const sourcemeta::jsontoolkit::Pointer &) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.defines("minimum") &&
           schema.defines("exclusiveMinimum") &&
           schema.at("minimum").is_number() &&
           schema.at("exclusiveMinimum").is_number();
  }

  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    if (transformer.schema().at("exclusiveMinimum") <
        transformer.schema().at("minimum")) {
      transformer.erase("exclusiveMinimum");
    } else {
      transformer.erase("minimum");
    }
  }
};
