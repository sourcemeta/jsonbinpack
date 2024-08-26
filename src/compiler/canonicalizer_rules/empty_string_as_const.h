class EmptyStringAsConst final : public sourcemeta::alterschema::Rule {
public:
  EmptyStringAsConst() : Rule("empty_string_as_const") {};

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
           schema.defines("maxLength") && schema.at("maxLength").is_integer() &&
           schema.at("maxLength").to_integer() == 0;
  }

  auto transform(sourcemeta::alterschema::Transformer &transformer) const
      -> void override {
    transformer.assign("const", sourcemeta::jsontoolkit::JSON{""});
    transformer.erase("maxLength");
  }
};
