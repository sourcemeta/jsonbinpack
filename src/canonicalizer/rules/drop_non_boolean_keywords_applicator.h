namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_heterogeneous
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/applicator | Y        |
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// If the `type` keyword from the Validation vocabulary is set to `boolean` and
/// the Applicator vocabulary is also in use, then keywords from the
/// Applicator vocabulary that do not apply to boolean JSON instances
/// can be removed.
///
/// \f[\frac{S.type = boolean \land (K_{object} \cup K_{array}) \cap S \not\in
/// \emptyset }{S \mapsto S \setminus (K_{object} \cup K_{array}) }\f]
///
/// Where:
///
/// \f[K_{object} = \{properties, patternProperties, additionalProperties,
/// dependentSchemas, propertyNames\}\f]
///
/// \f[K_{array} = \{prefixItems, contains, items\}\f]

class DropNonBooleanKeywordsApplicator final
    : public sourcemeta::alterschema::Rule {
public:
  DropNonBooleanKeywordsApplicator()
      : Rule("drop_non_boolean_keywords_applicator"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &draft,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return draft == "https://json-schema.org/draft/2020-12/schema" &&
           is_boolean_schema(schema, vocabularies) &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           sourcemeta::jsontoolkit::defines_any(schema,
                                                this->BLACKLIST_APPLICATOR);
  }

  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::erase_many(value, this->BLACKLIST_APPLICATOR);
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
} // namespace sourcemeta::jsonbinpack::canonicalizer
