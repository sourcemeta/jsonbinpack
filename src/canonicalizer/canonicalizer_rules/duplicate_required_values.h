namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_simplification
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// The `required` keyword from the Validation vocabulary represents a set of
/// object properties that must be defined. As such, duplicate choices do not
/// affect the result and can be removed.
///
/// \f[\frac{required \in dom(S) \land \#S.required \neq \#\{ x \mid S.required
/// \}}{S \mapsto S \cup \{ required \mapsto seq \; \{ x \mid S.required \} \}
/// }\f]

class DuplicateRequiredValues final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  DuplicateRequiredValues()
      : SchemaTransformRule("duplicate_required_values"){};

  /// The rule condition
  [[nodiscard]] auto condition(const sourcemeta::jsontoolkit::JSON &schema,
                               const std::string &dialect,
                               const std::set<std::string> &vocabularies,
                               const sourcemeta::jsontoolkit::Pointer &) const
      -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           schema.is_object() && schema.defines("required") &&
           schema.at("required").is_array() &&
           !is_unique(schema.at("required"));
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    auto collection = transformer.schema().at("required");
    std::sort(collection.as_array().begin(), collection.as_array().end());
    auto last =
        std::unique(collection.as_array().begin(), collection.as_array().end());
    collection.erase(last, collection.as_array().end());
    transformer.replace({"required"}, std::move(collection));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
