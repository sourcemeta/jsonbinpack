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

class ExclusiveMaximumAndMaximum final : public sourcemeta::alterschema::Rule {
public:
  ExclusiveMaximumAndMaximum() : Rule("exclusive_maximum_and_maximum"){};

  /// The rule condition
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &draft,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return draft == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           sourcemeta::jsontoolkit::defines(schema, "maximum") &&
           sourcemeta::jsontoolkit::defines(schema, "exclusiveMaximum") &&
           sourcemeta::jsontoolkit::is_number(
               sourcemeta::jsontoolkit::at(schema, "maximum")) &&
           sourcemeta::jsontoolkit::is_number(
               sourcemeta::jsontoolkit::at(schema, "exclusiveMaximum"));
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    const bool maximum_less_than_exclusive_maximum{
        sourcemeta::jsontoolkit::compare(
            sourcemeta::jsontoolkit::at(value, "maximum"),
            sourcemeta::jsontoolkit::at(value, "exclusiveMaximum"))};
    if (maximum_less_than_exclusive_maximum) {
      sourcemeta::jsontoolkit::erase(value, "exclusiveMaximum");
    } else {
      sourcemeta::jsontoolkit::erase(value, "maximum");
    }
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
