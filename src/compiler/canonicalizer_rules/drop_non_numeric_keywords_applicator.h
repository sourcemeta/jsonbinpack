class DropNonNumericKeywordsApplicator final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  DropNonNumericKeywordsApplicator()
      : SchemaTransformRule("drop_non_numeric_keywords_applicator"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON &schema,
            const std::string &dialect,
            const std::set<std::string> &vocabularies,
            const sourcemeta::jsontoolkit::Pointer &) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.defines("type") && schema.at("type").is_string() &&
           (schema.at("type").to_string() == "integer" ||
            schema.at("type").to_string() == "number") &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           schema.defines_any(this->BLACKLIST_APPLICATOR.cbegin(),
                              this->BLACKLIST_APPLICATOR.cend());
  }

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
