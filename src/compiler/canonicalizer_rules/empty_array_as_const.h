class EmptyArrayAsConst final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  EmptyArrayAsConst() : SchemaTransformRule("empty_array_as_const") {};

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
           schema.defines("maxItems") && schema.at("maxItems").is_integer() &&
           schema.at("maxItems").to_integer() == 0;
  }

  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.assign("const", sourcemeta::jsontoolkit::JSON::make_array());
    transformer.erase("maxItems");
  }
};
