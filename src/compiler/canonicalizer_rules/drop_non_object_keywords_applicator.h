/// @ingroup canonicalizer_rules_heterogeneous
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/applicator | Y        |
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// If the `type` keyword from the Validation vocabulary is set to `object` and
/// the Applicator vocabulary is also in use, then keywords from the
/// Applicator vocabulary that do not apply to object JSON instances
/// can be removed.
///
/// \f[\frac{S.type = object \land K \cap S \not\in \emptyset }{S
/// \mapsto S \setminus K }\f]
///
/// Where:
///
/// \f[K = \{ prefixItems, contains, items \}\f]

class DropNonObjectKeywordsApplicator final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  DropNonObjectKeywordsApplicator()
      : SchemaTransformRule("drop_non_object_keywords_applicator"){};

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
           schema.at("type").to_string() == "object" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           schema.defines_any(this->BLACKLIST_APPLICATOR.cbegin(),
                              this->BLACKLIST_APPLICATOR.cend());
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.erase_keys(this->BLACKLIST_APPLICATOR.cbegin(),
                           this->BLACKLIST_APPLICATOR.cend());
  }

private:
  const std::set<std::string> BLACKLIST_APPLICATOR{"prefixItems", "contains",
                                                   "items"};
};
