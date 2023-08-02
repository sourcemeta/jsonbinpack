namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_simplification
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/applicator | Y        |
///
/// The `allOf` keyword from the Applicator vocabulary represents a logical
/// conjunction. As such, duplicate branches do not affect the result and can be
/// removed.
///
/// \f[\frac{allOf \in dom(S) \land \#S.allOf \neq \#\{ x \mid S.allOf \}}{S
/// \mapsto S \cup \{ allOf \mapsto seq \; \{ x \mid S.allOf \} \} }\f]

class DuplicateAllOfBranches final : public sourcemeta::alterschema::Rule {
public:
  DuplicateAllOfBranches() : Rule("duplicate_allof_branches"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &draft,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return draft == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           sourcemeta::jsontoolkit::defines(schema, "allOf") &&
           sourcemeta::jsontoolkit::is_array(
               sourcemeta::jsontoolkit::at(schema, "allOf")) &&
           is_unique(sourcemeta::jsontoolkit::at(schema, "allOf"));
  }

  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    auto &collection{sourcemeta::jsontoolkit::at(value, "allOf")};
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
