namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_simplification
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/applicator | Y        |
///
/// The `anyOf` keyword from the Applicator vocabulary represents a logical
/// disjunction. As such, duplicate branches do not affect the result and can be
/// removed.
///
/// \f[\frac{anyOf \in dom(S) \land \#S.anyOf \neq \#\{ x \mid S.anyOf \}}{S
/// \mapsto S \cup \{ anyOf \mapsto seq \; \{ x \mid S.anyOf \} \} }\f]

class DuplicateAnyOfBranches final : public sourcemeta::alterschema::Rule {
public:
  DuplicateAnyOfBranches() : Rule("duplicate_anyof_branches"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &draft,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return draft == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           sourcemeta::jsontoolkit::defines(schema, "anyOf") &&
           sourcemeta::jsontoolkit::is_array(
               sourcemeta::jsontoolkit::at(schema, "anyOf")) &&
           is_unique(sourcemeta::jsontoolkit::at(schema, "anyOf"));
  }

  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    auto &collection{sourcemeta::jsontoolkit::at(value, "anyOf")};
    std::sort(sourcemeta::jsontoolkit::begin_array(collection),
              sourcemeta::jsontoolkit::end_array(collection),
              sourcemeta::jsontoolkit::compare);
    auto last = std::unique(sourcemeta::jsontoolkit::begin_array(collection),
                            sourcemeta::jsontoolkit::end_array(collection));
    sourcemeta::jsontoolkit::erase_many(
        collection, last, sourcemeta::jsontoolkit::end_array(collection));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
