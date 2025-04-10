class ThenWithoutIf final : public SchemaTransformRule {
public:
  ThenWithoutIf()
      : SchemaTransformRule{"then_without_if",
                            "The `then` keyword is meaningless "
                            "without the presence of the `if` keyword"} {};

  [[nodiscard]] auto condition(const sourcemeta::core::JSON &schema,
                               const std::string &,
                               const std::set<std::string> &vocabularies,
                               const sourcemeta::core::Pointer &) const
      -> bool override {
    return contains_any(
               vocabularies,
               {"https://json-schema.org/draft/2020-12/vocab/applicator",
                "https://json-schema.org/draft/2019-09/vocab/applicator",
                "http://json-schema.org/draft-07/schema#"}) &&
           schema.is_object() && schema.defines("then") &&
           !schema.defines("if");
  }

  auto transform(JSON &schema) const -> void override { schema.erase("then"); }
};
