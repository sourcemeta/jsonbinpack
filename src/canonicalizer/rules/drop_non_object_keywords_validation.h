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
    : public sourcemeta::alterschema::Rule {
public:
  DropNonObjectKeywordsValidation()
      : Rule("drop_non_object_keywords_validation"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &draft,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return draft == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::defines(schema, "type") &&
           sourcemeta::jsontoolkit::is_string(
               sourcemeta::jsontoolkit::at(schema, "type")) &&
           sourcemeta::jsontoolkit::to_string(
               sourcemeta::jsontoolkit::at(schema, "type")) == "object" &&
           sourcemeta::jsontoolkit::defines_any(schema,
                                                this->BLACKLIST_VALIDATION);
  }

  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::erase_many(value, this->BLACKLIST_VALIDATION);
  }

private:
  const std::set<std::string> BLACKLIST_VALIDATION{
      "minLength",        "maxLength",  "pattern",          "maximum",
      "exclusiveMinimum", "multipleOf", "exclusiveMaximum", "minimum",
      "minItems",         "maxItems",   "minContains",      "maxContains",
      "uniqueItems"};
};
} // namespace sourcemeta::jsonbinpack::canonicalizer
