namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_heterogeneous
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// If the `type` keyword from the Validation vocabulary is set to `object`,
/// then keywords from the Validation vocabulary that do not apply to object
/// JSON instances can be removed.
///
/// \f[\frac{S.type = object \land (K_{string} \cup K_{number} \cup K_{array})
/// \cap S \not\in \emptyset }{S \mapsto S \setminus (K_{string} \cup K_{number}
/// \cup K_{array}) }\f]
///
/// Where:
///
/// \f[K_{string} = \{minLength, maxLength, pattern\}\f]
///
/// \f[K_{number} = \{maximum, exclusiveMinimum, multipleOf, exclusiveMaximum,
/// minimum\}\f]
///
/// \f[K_{array} = \{minItems, maxItems, minContains, maxContains,
/// uniqueItems\}\f]

class DropNonObjectKeywordsValidation final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  DropNonObjectKeywordsValidation()
      : SchemaTransformRule("drop_non_object_keywords_validation"){};

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
           schema.defines_any(this->BLACKLIST_VALIDATION.cbegin(),
                              this->BLACKLIST_VALIDATION.cend());
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.erase_keys(this->BLACKLIST_VALIDATION.cbegin(),
                           this->BLACKLIST_VALIDATION.cend());
  }

private:
  const std::set<std::string> BLACKLIST_VALIDATION{
      "minLength",        "maxLength",  "pattern",          "maximum",
      "exclusiveMinimum", "multipleOf", "exclusiveMaximum", "minimum",
      "minItems",         "maxItems",   "minContains",      "maxContains",
      "uniqueItems"};
};
} // namespace sourcemeta::jsonbinpack::canonicalizer
