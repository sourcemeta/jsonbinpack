namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_implicit
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/applicator | Y        |
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// If the `type` keyword from the Validation vocabulary is set to `object` but
/// the `properties` keyword from the Applicator vocabulary is omitted, the
/// latter defaults to the empty object.
///
/// \f[\frac{S.type = object \land properties \not\in dom(S)}{S
/// \mapsto S \cup \{ properties \mapsto \{\} \}
/// }\f]

class ImplicitObjectProperties final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  ImplicitObjectProperties()
      : SchemaTransformRule("implicit_object_properties"){};

  /// The rule condition
  [[nodiscard]] auto condition(const sourcemeta::jsontoolkit::JSON &schema,
                               const std::string &dialect,
                               const std::set<std::string> &vocabularies,
                               const sourcemeta::jsontoolkit::Pointer &) const
      -> bool override {
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

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.assign("properties",
                       sourcemeta::jsontoolkit::JSON::make_object());
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
