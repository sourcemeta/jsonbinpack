namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_simplification
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// The `enum` keyword from the Validation vocabulary represents a logical
/// disjunction. As such, duplicate choices do not affect the result and can be
/// removed.
///
/// \f[\frac{enum \in dom(S) \land \#S.enum \neq \#\{ x \mid S.enum \}}{S
/// \mapsto S \cup \{ enum \mapsto seq \; \{ x \mid S.enum \} \} }\f]

class DuplicateEnumValues final : public sourcemeta::alterschema::Rule {
public:
  DuplicateEnumValues() : Rule("duplicate_enum_values"){};

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
           sourcemeta::jsontoolkit::defines(schema, "enum") &&
           sourcemeta::jsontoolkit::is_array(
               sourcemeta::jsontoolkit::at(schema, "enum")) &&
           is_unique(sourcemeta::jsontoolkit::at(schema, "enum"));
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    auto &collection{sourcemeta::jsontoolkit::at(value, "enum")};
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
