namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_superfluous
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/applicator | Y        |
///
/// Setting the `patternProperties` keyword from the Applicator vocabulary to
/// the empty object does not contribute any constraints to the given schema,
/// and thus can be removed.
///
/// \f[\frac{patternProperties \in dom(S) \land \#S.patternProperties = 0}{S
/// \mapsto S \setminus \{ patternProperties \}
/// }\f]

class EmptyPatternProperties final : public sourcemeta::alterschema::Rule {
public:
  EmptyPatternProperties() : Rule("empty_pattern_properties"){};

  /// The rule condition
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &draft,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return draft == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           sourcemeta::jsontoolkit::defines(schema, "patternProperties") &&
           sourcemeta::jsontoolkit::is_object(
               sourcemeta::jsontoolkit::at(schema, "patternProperties")) &&
           sourcemeta::jsontoolkit::empty(
               sourcemeta::jsontoolkit::at(schema, "patternProperties"));
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::erase(value, "patternProperties");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
