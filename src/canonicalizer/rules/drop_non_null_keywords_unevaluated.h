namespace sourcemeta::jsonbinpack::canonicalizer {

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
    : public sourcemeta::alterschema::Rule {
public:
  DropNonNullKeywordsUnevaluated()
      : Rule("drop_non_null_keywords_unevaluated"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &draft,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return draft == "https://json-schema.org/draft/2020-12/schema" &&
           is_null_schema(schema, vocabularies) &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/unevaluated") &&
           sourcemeta::jsontoolkit::defines_any(schema,
                                                this->BLACKLIST_UNEVALUATED);
  }

  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::erase_many(value, this->BLACKLIST_UNEVALUATED);
  }

private:
  const std::set<std::string> BLACKLIST_UNEVALUATED{"unevaluatedItems",
                                                    "unevaluatedProperties"};
};
} // namespace sourcemeta::jsonbinpack::canonicalizer
