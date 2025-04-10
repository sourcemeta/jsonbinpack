class ContentSchemaDefault final : public SchemaTransformRule {
public:
  ContentSchemaDefault()
      : SchemaTransformRule{
            "content_schema_default",
            "Setting the `contentSchema` keyword to the true schema "
            "does not add any further constraint"} {};

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
               {"https://json-schema.org/draft/2020-12/vocab/content",
                "https://json-schema.org/draft/2019-09/vocab/content"}) &&
           schema.is_object() && schema.defines("contentSchema") &&
           ((schema.at("contentSchema").is_boolean() &&
             schema.at("contentSchema").to_boolean()) ||
            (schema.at("contentSchema").is_object() &&
             schema.at("contentSchema").empty()));
  }

  auto transform(JSON &schema) const -> void override {
    schema.erase("contentSchema");
  }
};
