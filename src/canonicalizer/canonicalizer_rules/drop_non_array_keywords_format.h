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
/// If the `type` keyword from the Validation vocabulary is set to `array` and
/// either the Format Annotation or Format Assertion vocabularies are also in
/// use, then keywords from these vocabularies can be removed.
///
/// \f[\frac{S.type = array \land format \in dom(S) }{S
/// \mapsto S \setminus \{ format \} }\f]

class DropNonArrayKeywordsFormat final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  DropNonArrayKeywordsFormat()
      : SchemaTransformRule("drop_non_array_keywords_format"){};

  /// The rule condition
  [[nodiscard]] auto condition(const sourcemeta::jsontoolkit::JSON &schema,
                               const std::string &dialect,
                               const std::set<std::string> &vocabularies,
                               const sourcemeta::jsontoolkit::Pointer &) const
      -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.defines("type") && schema.at("type").is_string() &&
           schema.at("type").to_string() == "array" &&
           (vocabularies.contains("https://json-schema.org/draft/2020-12/vocab/"
                                  "format-annotation") ||
            vocabularies.contains("https://json-schema.org/draft/2020-12/vocab/"
                                  "format-assertion")) &&
           schema.defines_any(this->BLACKLIST_FORMAT.cbegin(),
                              this->BLACKLIST_FORMAT.cend());
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.erase_keys(this->BLACKLIST_FORMAT.cbegin(),
                           this->BLACKLIST_FORMAT.cend());
  }

private:
  const std::set<std::string> BLACKLIST_FORMAT{"format"};
};
} // namespace sourcemeta::jsonbinpack::canonicalizer
