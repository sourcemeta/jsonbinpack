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

class ExclusiveMinimumAndMinimum final : public sourcemeta::alterschema::Rule {
public:
  ExclusiveMinimumAndMinimum() : Rule("exclusive_minimum_and_minimum"){};

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
           sourcemeta::jsontoolkit::defines(schema, "minimum") &&
           sourcemeta::jsontoolkit::defines(schema, "exclusiveMinimum") &&
           sourcemeta::jsontoolkit::is_number(
               sourcemeta::jsontoolkit::at(schema, "minimum")) &&
           sourcemeta::jsontoolkit::is_number(
               sourcemeta::jsontoolkit::at(schema, "exclusiveMinimum"));
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    const bool exclusive_minimum_less_than_minimum{
        sourcemeta::jsontoolkit::compare(
            sourcemeta::jsontoolkit::at(value, "exclusiveMinimum"),
            sourcemeta::jsontoolkit::at(value, "minimum"))};
    if (exclusive_minimum_less_than_minimum) {
      sourcemeta::jsontoolkit::erase(value, "exclusiveMinimum");
    } else {
      sourcemeta::jsontoolkit::erase(value, "minimum");
    }
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
