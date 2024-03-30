class EnumSingleton final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  EnumSingleton()
      : sourcemeta::jsontoolkit::SchemaTransformRule("enum_singleton"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON &schema,
            const std::string &dialect,
            const std::set<std::string> &vocabularies,
            const sourcemeta::jsontoolkit::Pointer &) const -> bool override {
    return !is_encoding(schema) &&
           dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.defines("enum") && schema.at("enum").is_array() &&
           schema.at("enum").size() == 1;
  }

  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    auto options = sourcemeta::jsontoolkit::JSON::make_object();
    options.assign("value", transformer.schema().at("enum").at(0));
    make_encoding(transformer, "CONST_NONE", options);
  }
};
