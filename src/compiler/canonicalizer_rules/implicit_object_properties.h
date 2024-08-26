class ImplicitObjectProperties final : public sourcemeta::alterschema::Rule {
public:
  ImplicitObjectProperties() : Rule("implicit_object_properties") {};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON &schema,
            const std::string &dialect,
            const std::set<std::string> &vocabularies,
            const sourcemeta::jsontoolkit::Pointer &) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           schema.is_object() && schema.defines("type") &&
           schema.at("type").is_string() &&
           schema.at("type").to_string() == "object" &&
           !schema.defines("properties");
  }

  auto transform(sourcemeta::alterschema::Transformer &transformer) const
      -> void override {
    transformer.assign("properties",
                       sourcemeta::jsontoolkit::JSON::make_object());
  }
};
