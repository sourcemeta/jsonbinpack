namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_superfluous
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/applicator | Y        |
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// Declaring the `maxContains` keyword from the Validation
/// vocabulary without also declaring the `contains` keyword from the Applicator
/// vocabulary does not contribute any constraints to the given schema, and thus
/// can be removed.
///
/// \f[\frac{maxContains \in dom(S) \land contains \not\in dom(S) }{S \mapsto S
/// \setminus \{ maxContains \} }\f]

class MaxContainsWithoutContains final : public sourcemeta::alterschema::Rule {
public:
  MaxContainsWithoutContains() : Rule("max_contains_without_contains"){};

  /// The rule condition
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &draft,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return draft == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           sourcemeta::jsontoolkit::defines(schema, "maxContains") &&
           !sourcemeta::jsontoolkit::defines(schema, "contains");
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::erase(value, "maxContains");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
