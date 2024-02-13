/// @ingroup canonicalizer_rules_heterogeneous
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/applicator | Y        |
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// If the `type` keyword from the Validation vocabulary is set to `null` and
/// the Applicator vocabulary is also in use, then keywords from the
/// Applicator vocabulary that do not apply to null JSON instances
/// can be removed.
///
/// \f[\frac{S.type = null \land (K_{object} \cup K_{array}) \cap S \not\in
/// \emptyset }{S \mapsto S \setminus (K_{object} \cup K_{array}) }\f]
///
/// Where:
///
/// \f[K_{object} = \{properties, patternProperties, additionalProperties,
/// dependentSchemas, propertyNames\}\f]
///
/// \f[K_{array} = \{prefixItems, contains, items\}\f]

class DropNonNullKeywordsApplicator final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  DropNonNullKeywordsApplicator()
      : SchemaTransformRule("drop_non_null_keywords_applicator"){};

  /// The rule condition
  [[nodiscard]] auto condition(const sourcemeta::jsontoolkit::JSON &schema,
                               const std::string &dialect,
                               const std::set<std::string> &vocabularies,
                               const sourcemeta::jsontoolkit::Pointer &) const
      -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           is_null_schema(schema, vocabularies) &&
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
  const std::set<std::string> BLACKLIST_APPLICATOR{"properties",
                                                   "patternProperties",
                                                   "additionalProperties",
                                                   "dependentSchemas",
                                                   "propertyNames",
                                                   "prefixItems",
                                                   "contains",
                                                   "items"};
};
