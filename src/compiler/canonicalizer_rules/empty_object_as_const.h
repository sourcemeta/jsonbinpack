class EmptyObjectAsConst final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  EmptyObjectAsConst() : SchemaTransformRule("empty_object_as_const") {};

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
           schema.at("type").to_string() == "object" &&
           schema.defines("maxProperties") &&
           schema.at("maxProperties").is_integer() &&
           schema.at("maxProperties").to_integer() == 0;
  }

  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.assign("const", sourcemeta::jsontoolkit::JSON::make_object());
    transformer.erase("maxProperties");
  }
};
