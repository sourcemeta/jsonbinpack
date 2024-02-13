/// @ingroup canonicalizer_rules_heterogeneous
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                          | Required |
/// |---------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/unevaluated | Y        |
/// | https://json-schema.org/draft/2020-12/vocab/validation  | Y        |
///
/// If the `type` keyword from the Validation vocabulary is set to `array` and
/// the Unevaluated vocabulary is in use, then keywords from the
/// Unevaluated vocabulary that do not apply to array JSON instances can be
/// removed.
///
/// \f[\frac{S.type = array \land unevaluatedProperties \in dom(S) }{S
/// \mapsto S \setminus \{ unevaluatedProperties \} }\f]

class DropNonArrayKeywordsUnevaluated final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  DropNonArrayKeywordsUnevaluated()
      : SchemaTransformRule("drop_non_array_keywords_unevaluated"){};

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
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/unevaluated") &&
           schema.defines_any(this->BLACKLIST_UNEVALUATED.cbegin(),
                              this->BLACKLIST_UNEVALUATED.cend());
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.erase_keys(this->BLACKLIST_UNEVALUATED.cbegin(),
                           this->BLACKLIST_UNEVALUATED.cend());
  }

private:
  const std::set<std::string> BLACKLIST_UNEVALUATED{"unevaluatedProperties"};
};
