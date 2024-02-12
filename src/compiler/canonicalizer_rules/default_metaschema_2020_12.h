namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_implicit
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                   | Required |
/// |--------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/core | Y        |
///
/// If the 2020-12 draft is in use for the schema does not declare the
/// `$schema` keyword from the Core vocabulary, then it is sensible
/// to default to the official 2020-12 metaschema.
///
/// \f[\frac{\$schema \not\in dom(S)}{S
/// \mapsto S \cup \{ \$schema \mapsto
/// \textsl{https://json-schema.org/draft/2020-12/schema} \} }\f]

class DefaultMetaschema_2020_12 final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  DefaultMetaschema_2020_12()
      : SchemaTransformRule("default_metaschema_2020_12"){};

  /// The rule condition
  [[nodiscard]] auto condition(
      const sourcemeta::jsontoolkit::JSON &schema, const std::string &dialect,
      const std::set<std::string> &vocabularies,
      const sourcemeta::jsontoolkit::Pointer &level) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/core") &&
           schema.is_object() && !schema.defines("$schema") && level.empty();
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.assign("$schema",
                       sourcemeta::jsontoolkit::JSON{
                           "https://json-schema.org/draft/2020-12/schema"});
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
