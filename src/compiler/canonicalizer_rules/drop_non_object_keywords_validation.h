class DropNonObjectKeywordsValidation final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  DropNonObjectKeywordsValidation()
      : SchemaTransformRule("drop_non_object_keywords_validation") {};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON &schema,
            const std::string &dialect,
            const std::set<std::string> &vocabularies,
            const sourcemeta::jsontoolkit::Pointer &) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.defines("type") && schema.at("type").is_string() &&
           schema.at("type").to_string() == "object" &&
           schema.defines_any(this->BLACKLIST_VALIDATION.cbegin(),
                              this->BLACKLIST_VALIDATION.cend());
  }

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
