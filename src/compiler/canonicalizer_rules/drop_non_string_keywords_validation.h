class DropNonStringKeywordsValidation final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  DropNonStringKeywordsValidation()
      : SchemaTransformRule("drop_non_string_keywords_validation"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON &schema,
            const std::string &dialect,
            const std::set<std::string> &vocabularies,
            const sourcemeta::jsontoolkit::Pointer &) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.defines("type") && schema.at("type").is_string() &&
           schema.at("type").to_string() == "string" &&
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
      "maximum",     "exclusiveMinimum",  "multipleOf",    "exclusiveMaximum",
      "minimum",     "dependentRequired", "minProperties", "maxProperties",
      "required",    "minItems",          "maxItems",      "minContains",
      "maxContains", "uniqueItems"};
};
