namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_heterogeneous
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                                | Required |
/// |---------------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/format-annotation | N        |
/// | https://json-schema.org/draft/2020-12/vocab/format-assertion  | N        |
/// | https://json-schema.org/draft/2020-12/vocab/validation        | Y        |
///
/// If the `type` keyword from the Validation vocabulary is set to `boolean` and
/// either the Format Annotation or Format Assertion vocabularies are also in
/// use, then keywords from these vocabularies can be removed.
///
/// \f[\frac{S.type = boolean \land format \in dom(S) }{S
/// \mapsto S \setminus \{ format \} }\f]

class DropNonBooleanKeywordsFormat final
    : public sourcemeta::alterschema::Rule {
public:
  DropNonBooleanKeywordsFormat() : Rule("drop_non_boolean_keywords_format"){};

  /// The rule condition
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &draft,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return draft == "https://json-schema.org/draft/2020-12/schema" &&
           is_boolean_schema(schema, vocabularies) &&
           (vocabularies.contains("https://json-schema.org/draft/2020-12/vocab/"
                                  "format-annotation") ||
            vocabularies.contains("https://json-schema.org/draft/2020-12/vocab/"
                                  "format-assertion")) &&
           sourcemeta::jsontoolkit::defines_any(schema, this->BLACKLIST_FORMAT);
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::erase_many(value, this->BLACKLIST_FORMAT);
  }

private:
  const std::set<std::string> BLACKLIST_FORMAT{"format"};
};
} // namespace sourcemeta::jsonbinpack::canonicalizer
