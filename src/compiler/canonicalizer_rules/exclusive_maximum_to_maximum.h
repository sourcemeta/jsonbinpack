class ExclusiveMaximumToMaximum final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  ExclusiveMaximumToMaximum()
      : SchemaTransformRule("exclusive_maximum_to_maximum"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON &schema,
            const std::string &dialect,
            const std::set<std::string> &vocabularies,
            const sourcemeta::jsontoolkit::Pointer &) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.defines("exclusiveMaximum") &&
           schema.at("exclusiveMaximum").is_number() &&
           !schema.defines("maximum");
  }

  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    auto new_maximum = transformer.schema().at("exclusiveMaximum");
    new_maximum += sourcemeta::jsontoolkit::JSON{-1};
    transformer.assign("maximum", new_maximum);
    transformer.erase("exclusiveMaximum");
  }
};
