class ExclusiveMinimumToMinimum final : public sourcemeta::alterschema::Rule {
public:
  ExclusiveMinimumToMinimum() : Rule("exclusive_minimum_to_minimum") {};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON &schema,
            const std::string &dialect,
            const std::set<std::string> &vocabularies,
            const sourcemeta::jsontoolkit::Pointer &) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.defines("exclusiveMinimum") &&
           schema.at("exclusiveMinimum").is_number() &&
           !schema.defines("minimum");
  }

  auto transform(sourcemeta::alterschema::Transformer &transformer) const
      -> void override {
    auto new_minimum = transformer.schema().at("exclusiveMinimum");
    new_minimum += sourcemeta::jsontoolkit::JSON{1};
    transformer.assign("minimum", new_minimum);
    transformer.erase("exclusiveMinimum");
  }
};
