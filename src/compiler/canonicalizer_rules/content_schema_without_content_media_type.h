class ContentSchemaWithoutContentMediaType final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  ContentSchemaWithoutContentMediaType()
      : SchemaTransformRule("content_schema_without_content_media_type") {};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON &schema,
            const std::string &dialect,
            const std::set<std::string> &vocabularies,
            const sourcemeta::jsontoolkit::Pointer &) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/content") &&
           schema.is_object() && schema.defines("contentSchema") &&
           !schema.defines("contentMediaType");
  }

  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.erase("contentSchema");
  }
};
