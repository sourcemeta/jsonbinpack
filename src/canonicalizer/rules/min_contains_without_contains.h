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
/// Declaring the `minContains` keyword from the Validation
/// vocabulary without also declaring the `contains` keyword from the Applicator
/// vocabulary does not contribute any constraints to the given schema, and thus
/// can be removed.
///
/// \f[\frac{minContains \in dom(S) \land contains \not\in dom(S) }{S \mapsto S
/// \setminus \{ minContains \} }\f]

class MinContainsWithoutContains final : public sourcemeta::alterschema::Rule {
public:
  MinContainsWithoutContains() : Rule("min_contains_without_contains"){};
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
           sourcemeta::jsontoolkit::defines(schema, "minContains") &&
           !sourcemeta::jsontoolkit::defines(schema, "contains");
  }

  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::erase(value, "minContains");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
