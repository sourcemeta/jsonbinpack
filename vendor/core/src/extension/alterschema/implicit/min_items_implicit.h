class MinItemsImplicit final : public SchemaTransformRule {
public:
  MinItemsImplicit()
      : SchemaTransformRule{"min_items_implicit",
                            "Every array has a minimum size of zero items"} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::core::Vocabularies &vocabularies,
            const sourcemeta::core::SchemaFrame &,
            const sourcemeta::core::SchemaFrame::Location &,
            const sourcemeta::core::SchemaWalker &,
            const sourcemeta::core::SchemaResolver &) const -> bool override {
    return contains_any(vocabularies,
                        {"http://json-schema.org/draft-07/schema#",
                         "http://json-schema.org/draft-06/schema#",
                         "http://json-schema.org/draft-04/schema#",
                         "http://json-schema.org/draft-03/schema#",
                         "http://json-schema.org/draft-02/hyper-schema#",
                         "http://json-schema.org/draft-01/hyper-schema#"}) &&
           schema.is_object() && schema.defines("type") &&
           schema.at("type").is_string() &&
           schema.at("type").to_string() == "array" &&
           !schema.defines("minItems");
  }

  auto transform(JSON &schema) const -> void override {
    schema.assign("minItems", sourcemeta::core::JSON{0});
  }
};
