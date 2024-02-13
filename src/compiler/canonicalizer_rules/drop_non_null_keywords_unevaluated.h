/// @ingroup canonicalizer_rules_heterogeneous
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                          | Required |
/// |---------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/unevaluated | Y        |
/// | https://json-schema.org/draft/2020-12/vocab/validation  | Y        |
///
/// If the `type` keyword from the Validation vocabulary is set to `null` and
/// the Unevaluated vocabulary is in use, then keywords from the
/// Unevaluated vocabulary that do not apply to null JSON instances can be
/// removed.
///
/// \f[\frac{S.type = null \land K \subseteq dom(S) }{S
/// \mapsto S \setminus K }\f]
///
/// Where:
///
/// \f[K = \{ unevaluatedItems, unevaluatedProperties \}\f]

class DropNonNullKeywordsUnevaluated final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  DropNonNullKeywordsUnevaluated()
      : SchemaTransformRule("drop_non_null_keywords_unevaluated"){};

  /// The rule condition
  [[nodiscard]] auto condition(const sourcemeta::jsontoolkit::JSON &schema,
                               const std::string &dialect,
                               const std::set<std::string> &vocabularies,
                               const sourcemeta::jsontoolkit::Pointer &) const
      -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           is_null_schema(schema, vocabularies) &&
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
  const std::set<std::string> BLACKLIST_UNEVALUATED{"unevaluatedItems",
                                                    "unevaluatedProperties"};
};
