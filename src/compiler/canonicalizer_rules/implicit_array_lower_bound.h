class ImplicitArrayLowerBound final : public sourcemeta::alterschema::Rule {
public:
  ImplicitArrayLowerBound() : Rule("implicit_array_lower_bound", "TODO") {};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON &schema,
            const std::string &dialect,
            const std::set<std::string> &vocabularies,
            const sourcemeta::jsontoolkit::Pointer &) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.defines("type") &&
           schema.at("type").is_string() &&
           schema.at("type").to_string() == "array" &&
           !schema.defines("minItems");
  }

  auto transform(sourcemeta::alterschema::Transformer &transformer) const
      -> void override {
    transformer.assign("minItems", sourcemeta::jsontoolkit::JSON{0});
  }
};
