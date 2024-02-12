namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_simplification
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// Both the `minimum` and `exclusiveMinimum` keywords from the Validation
/// vocabulary express the same lower bound constraint. If both are present,
/// only the most restrictive one can remain.
///
/// If `exclusiveMinimum` is less than `minimum`:
///
/// \f[\frac{\{ minimum, exclusiveMinimum \} \subseteq dom(S) \land
/// S.exclusiveMinimum < S.minimum}{S \mapsto S \setminus \{ exclusiveMinimum \}
/// }\f]
///
/// Otherwise:
///
/// \f[\frac{\{ minimum, exclusiveMinimum \} \subseteq dom(S) \land
/// S.exclusiveMinimum \geq S.minimum}{S \mapsto S \setminus \{ minimum \}
/// }\f]

class ExclusiveMinimumAndMinimum final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  ExclusiveMinimumAndMinimum()
      : SchemaTransformRule("exclusive_minimum_and_minimum"){};

  /// The rule condition
  [[nodiscard]] auto condition(const sourcemeta::jsontoolkit::JSON &schema,
                               const std::string &dialect,
                               const std::set<std::string> &vocabularies,
                               const sourcemeta::jsontoolkit::Pointer &) const
      -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.defines("minimum") &&
           schema.defines("exclusiveMinimum") &&
           schema.at("minimum").is_number() &&
           schema.at("exclusiveMinimum").is_number();
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    if (transformer.schema().at("exclusiveMinimum") <
        transformer.schema().at("minimum")) {
      transformer.erase("exclusiveMinimum");
    } else {
      transformer.erase("minimum");
    }
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
