namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_heterogeneous
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// If the `type` keyword from the Validation vocabulary is set to `null`, then
/// keywords from the Validation vocabulary that do not apply to null JSON
/// instances can be removed.
///
/// \f[\frac{S.type = null \land (K_{string} \cup K_{number} \cup K_{object}
/// \cup K_{array}) \cap S \not\in \emptyset }{S \mapsto S \setminus (K_{string}
/// \cup K_{number} \cup K_{object} \cup K_{array}) }\f]
///
/// Where:
///
/// \f[K_{string} = \{minLength, maxLength, pattern\}\f]
///
/// \f[K_{number} = \{maximum, exclusiveMinimum, multipleOf, exclusiveMaximum,
/// minimum\}\f]
///
/// \f[K_{object} = \{dependentRequired, minProperties, maxProperties,
/// required\}\f]
///
/// \f[K_{array} = \{minItems, maxItems, minContains, maxContains,
/// uniqueItems\}\f]

class DropNonNullKeywordsValidation final
    : public sourcemeta::alterschema::Rule {
public:
  DropNonNullKeywordsValidation() : Rule("drop_non_null_keywords_validation"){};

  /// The rule condition
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &draft,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return draft == "https://json-schema.org/draft/2020-12/schema" &&
           is_null_schema(schema, vocabularies) &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::defines_any(schema,
                                                this->BLACKLIST_VALIDATION);
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::erase_many(value, this->BLACKLIST_VALIDATION);
  }

private:
  const std::set<std::string> BLACKLIST_VALIDATION{
      "minLength",         "maxLength",     "pattern",          "maximum",
      "exclusiveMinimum",  "multipleOf",    "exclusiveMaximum", "minimum",
      "dependentRequired", "minProperties", "maxProperties",    "required",
      "minItems",          "maxItems",      "minContains",      "maxContains",
      "uniqueItems"};
};
} // namespace sourcemeta::jsonbinpack::canonicalizer
