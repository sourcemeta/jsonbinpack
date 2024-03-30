class EmptyPatternProperties final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  EmptyPatternProperties() : SchemaTransformRule("empty_pattern_properties"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON &schema,
            const std::string &dialect,
            const std::set<std::string> &vocabularies,
            const sourcemeta::jsontoolkit::Pointer &) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           schema.is_object() && schema.defines("patternProperties") &&
           schema.at("patternProperties").is_object() &&
           schema.at("patternProperties").empty();
  }

  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.erase("patternProperties");
  }
};
