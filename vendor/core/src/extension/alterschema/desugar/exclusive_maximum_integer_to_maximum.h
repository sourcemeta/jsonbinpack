class ExclusiveMaximumIntegerToMaximum final : public SchemaTransformRule {
public:
  ExclusiveMaximumIntegerToMaximum()
      : SchemaTransformRule{
            "exclusive_maximum_integer_to_maximum",
            "Setting `exclusiveMaximum` when `type` is `integer` is syntax "
            "sugar for `maximum`"} {};

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
           schema.is_object() && schema.defines("type") &&
           schema.at("type").is_string() &&
           schema.at("type").to_string() == "integer" &&
           schema.defines("exclusiveMaximum") &&
           schema.at("exclusiveMaximum").is_number() &&
           !schema.defines("maximum");
  }

  auto transform(JSON &schema) const -> void override {
    if (schema.at("exclusiveMaximum").is_integer()) {
      auto new_maximum = schema.at("exclusiveMaximum");
      new_maximum += sourcemeta::core::JSON{-1};
      schema.at("exclusiveMaximum").into(new_maximum);
      schema.rename("exclusiveMaximum", "maximum");
    } else {
      const auto current{schema.at("exclusiveMaximum").to_real()};
      const auto new_value{static_cast<std::int64_t>(std::floor(current))};
      schema.at("exclusiveMaximum").into(sourcemeta::core::JSON{new_value});
      schema.rename("exclusiveMaximum", "maximum");
    }
  }
};
