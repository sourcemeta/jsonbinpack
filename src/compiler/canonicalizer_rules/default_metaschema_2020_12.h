class DefaultMetaschema_2020_12 final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  DefaultMetaschema_2020_12()
      : SchemaTransformRule("default_metaschema_2020_12") {};

  [[nodiscard]] auto condition(
      const sourcemeta::jsontoolkit::JSON &schema, const std::string &dialect,
      const std::set<std::string> &vocabularies,
      const sourcemeta::jsontoolkit::Pointer &level) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/core") &&
           schema.is_object() && !schema.defines("$schema") && level.empty();
  }

  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.assign("$schema",
                       sourcemeta::jsontoolkit::JSON{
                           "https://json-schema.org/draft/2020-12/schema"});
  }
};
