class ImplicitTypeUnion final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  ImplicitTypeUnion() : SchemaTransformRule("implicit_type_union") {};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON &schema,
            const std::string &dialect,
            const std::set<std::string> &vocabularies,
            const sourcemeta::jsontoolkit::Pointer &) const -> bool override {
    const bool has_core_blacklist{
        vocabularies.contains(
            "https://json-schema.org/draft/2020-12/vocab/core") &&
        schema.defines_any({"$ref", "$dynamicRef"})};
    const bool has_applicator_blacklist{
        vocabularies.contains(
            "https://json-schema.org/draft/2020-12/vocab/applicator") &&
        schema.defines_any(
            {"anyOf", "allOf", "oneOf", "not", "if", "then", "else"})};
    const bool has_validation_blacklist{
        vocabularies.contains(
            "https://json-schema.org/draft/2020-12/vocab/validation") &&
        schema.defines_any({"type", "const", "enum"})};

    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && !has_core_blacklist &&
           !has_applicator_blacklist && !has_validation_blacklist;
  }

  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    sourcemeta::jsontoolkit::JSON types =
        sourcemeta::jsontoolkit::JSON::make_array();

    // All possible JSON Schema types
    // See
    // https://json-schema.org/draft/2020-12/json-schema-validation.html#rfc.section.6.1.1
    types.push_back(sourcemeta::jsontoolkit::JSON{"null"});
    types.push_back(sourcemeta::jsontoolkit::JSON{"boolean"});
    types.push_back(sourcemeta::jsontoolkit::JSON{"object"});
    types.push_back(sourcemeta::jsontoolkit::JSON{"array"});
    types.push_back(sourcemeta::jsontoolkit::JSON{"string"});
    types.push_back(sourcemeta::jsontoolkit::JSON{"number"});
    types.push_back(sourcemeta::jsontoolkit::JSON{"integer"});

    transformer.assign("type", std::move(types));
  }
};
