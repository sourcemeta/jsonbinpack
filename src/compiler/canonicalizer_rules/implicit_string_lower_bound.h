class ImplicitStringLowerBound final : public sourcemeta::alterschema::Rule {
public:
  ImplicitStringLowerBound() : Rule("implicit_string_lower_bound", "TODO") {};

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
           schema.at("type").to_string() == "string" &&
           !schema.defines("minLength");
  }

  auto transform(sourcemeta::alterschema::Transformer &transformer) const
      -> void override {
    transformer.assign("minLength", sourcemeta::jsontoolkit::JSON{0});
  }
};
