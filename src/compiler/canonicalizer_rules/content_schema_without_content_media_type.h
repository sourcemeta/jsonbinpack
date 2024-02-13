/// @ingroup canonicalizer_rules_superfluous
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                      | Required |
/// |-----------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/content | Y        |
///
/// The JSON Schema Content vocabulary the `contentSchema` keyword, which
/// is set to a schema that defines the given string-encoded value. However,
/// the `contentSchema` keyword is only considered if the `contentMediaType`
/// keyword from the Content vocabulary is also set.
///
/// \f[\frac{contentSchema \in dom(S) \land contentMediaType \not\in dom(S)}{S
/// \mapsto S \setminus \{contentSchema\} }\f]
class ContentSchemaWithoutContentMediaType final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  ContentSchemaWithoutContentMediaType()
      : SchemaTransformRule("content_schema_without_content_media_type"){};

  /// The rule condition
  [[nodiscard]] auto condition(const sourcemeta::jsontoolkit::JSON &schema,
                               const std::string &dialect,
                               const std::set<std::string> &vocabularies,
                               const sourcemeta::jsontoolkit::Pointer &) const
      -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/content") &&
           schema.is_object() && schema.defines("contentSchema") &&
           !schema.defines("contentMediaType");
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.erase("contentSchema");
  }
};
