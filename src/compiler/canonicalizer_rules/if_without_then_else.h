class IfWithoutThenElse final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  IfWithoutThenElse() : SchemaTransformRule("if_without_then_else"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON &schema,
            const std::string &dialect,
            const std::set<std::string> &vocabularies,
            const sourcemeta::jsontoolkit::Pointer &) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           schema.is_object() && schema.defines("if") &&
           !schema.defines("then") && !schema.defines("else");
  }

  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.erase("if");
  }
};
