namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_simplification
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// Both the `maximum` and `exclusiveMaximum` keywords from the Validation
/// vocabulary express the same upper bound constraint. If both are present,
/// only the most restrictive one can remain.
///
/// If `maximum` is less than or equal to `exclusiveMaximum`:
///
/// \f[\frac{\{ maximum, exclusiveMaximum \} \subseteq dom(S) \land S.maximum
/// \leq S.exclusiveMaximum}{S \mapsto S \setminus \{ exclusiveMaximum \}
/// }\f]
///
/// Otherwise:
///
/// \f[\frac{\{ maximum, exclusiveMaximum \} \subseteq dom(S) \land S.maximum >
/// S.exclusiveMaximum}{S \mapsto S \setminus \{ maximum \}
/// }\f]

class ExclusiveMaximumAndMaximum final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  ExclusiveMaximumAndMaximum()
      : SchemaTransformRule("exclusive_maximum_and_maximum"){};

  /// The rule condition
  [[nodiscard]] auto condition(const sourcemeta::jsontoolkit::JSON &schema,
                               const std::string &dialect,
                               const std::set<std::string> &vocabularies,
                               const sourcemeta::jsontoolkit::Pointer &) const
      -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.defines("maximum") &&
           schema.defines("exclusiveMaximum") &&
           schema.at("maximum").is_number() &&
           schema.at("exclusiveMaximum").is_number();
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    if (transformer.schema().at("maximum") <
        transformer.schema().at("exclusiveMaximum")) {
      transformer.erase("exclusiveMaximum");
    } else {
      transformer.erase("maximum");
    }
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
