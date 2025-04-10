class ExclusiveMaximumNumberAndMaximum final : public SchemaTransformRule {
public:
  ExclusiveMaximumNumberAndMaximum()
      : SchemaTransformRule{
            "exclusive_maximum_number_and_maximum",
            "Setting both `exclusiveMaximum` and `maximum` at the same time "
            "is considered an anti-pattern. You should choose one"} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::core::Vocabularies &vocabularies,
            const sourcemeta::core::SchemaFrame &,
            const sourcemeta::core::SchemaFrame::Location &,
            const sourcemeta::core::SchemaWalker &,
            const sourcemeta::core::SchemaResolver &) const -> bool override {
    return contains_any(
               vocabularies,
               {"https://json-schema.org/draft/2020-12/vocab/validation",
                "https://json-schema.org/draft/2019-09/vocab/validation",
                "http://json-schema.org/draft-07/schema#",
                "http://json-schema.org/draft-06/schema#"}) &&
           schema.is_object() && schema.defines("maximum") &&
           schema.defines("exclusiveMaximum") &&
           schema.at("maximum").is_number() &&
           schema.at("exclusiveMaximum").is_number();
  }

  auto transform(JSON &schema) const -> void override {
    if (schema.at("maximum") < schema.at("exclusiveMaximum")) {
      schema.erase("exclusiveMaximum");
    } else {
      schema.erase("maximum");
    }
  }
};
