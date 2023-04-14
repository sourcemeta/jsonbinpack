namespace sourcemeta::jsonbinpack::canonicalizer {

class DropNonNumericKeywordsValidation final
    : public sourcemeta::alterschema::Rule {
public:
  DropNonNumericKeywordsValidation()
      : Rule("drop_non_numeric_keywords_validation"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::defines(schema, "type") &&
           sourcemeta::jsontoolkit::is_string(
               sourcemeta::jsontoolkit::at(schema, "type")) &&
           (sourcemeta::jsontoolkit::to_string(
                sourcemeta::jsontoolkit::at(schema, "type")) == "integer" ||
            sourcemeta::jsontoolkit::to_string(
                sourcemeta::jsontoolkit::at(schema, "type")) == "number") &&
           sourcemeta::jsontoolkit::defines_any(schema,
                                                this->BLACKLIST_VALIDATION);
  }

  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::erase_many(value, this->BLACKLIST_VALIDATION);
  }

private:
  const std::set<std::string> BLACKLIST_VALIDATION{
      "minLength",     "maxLength",     "pattern",     "dependentRequired",
      "minProperties", "maxProperties", "required",    "minItems",
      "maxItems",      "minContains",   "maxContains", "uniqueItems"};
};
} // namespace sourcemeta::jsonbinpack::canonicalizer
