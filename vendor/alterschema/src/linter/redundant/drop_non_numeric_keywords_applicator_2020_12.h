class DropNonNumericKeywordsApplicator_2020_12 final : public Rule {
public:
  DropNonNumericKeywordsApplicator_2020_12()
      : Rule{"drop_non_numeric_keywords_applicator_2020_12",
             "Keywords that don't apply to numbers will never match if the "
             "instance is guaranteed to be a number"} {};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON &schema, const std::string &,
            const std::set<std::string> &vocabularies,
            const sourcemeta::jsontoolkit::Pointer &) const -> bool override {
    return vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.defines("type") &&
           schema.at("type").is_string() &&
           (schema.at("type").to_string() == "integer" ||
            schema.at("type").to_string() == "number") &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           schema.defines_any(this->BLACKLIST.cbegin(), this->BLACKLIST.cend());
  }

  auto transform(Transformer &transformer) const -> void override {
    transformer.erase_keys(this->BLACKLIST.cbegin(), this->BLACKLIST.cend());
  }

private:
  const std::set<std::string> BLACKLIST{"properties",
                                        "patternProperties",
                                        "additionalProperties",
                                        "dependentSchemas",
                                        "propertyNames",
                                        "prefixItems",
                                        "contains",
                                        "items"};
};
