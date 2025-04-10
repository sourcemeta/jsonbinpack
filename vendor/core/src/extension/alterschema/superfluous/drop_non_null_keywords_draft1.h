class DropNonNullKeywords_Draft1 final : public SchemaTransformRule {
public:
  DropNonNullKeywords_Draft1()
      : SchemaTransformRule{
            "drop_non_null_keywords_draft1",
            "Keywords that don't apply to null values will never match if the "
            "instance is guaranteed to be null"} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::core::Vocabularies &vocabularies,
            const sourcemeta::core::SchemaFrame &,
            const sourcemeta::core::SchemaFrame::Location &,
            const sourcemeta::core::SchemaWalker &,
            const sourcemeta::core::SchemaResolver &) const -> bool override {
    return vocabularies.contains(
               "http://json-schema.org/draft-01/hyper-schema#") &&
           schema.is_object() && schema.defines("type") &&
           schema.at("type").is_string() &&
           schema.at("type").to_string() == "null" &&
           schema.defines_any(this->BLACKLIST.cbegin(), this->BLACKLIST.cend());
  }

  auto transform(JSON &schema) const -> void override {
    schema.erase_keys(this->BLACKLIST.cbegin(), this->BLACKLIST.cend());
  }

private:
  const std::set<std::string> BLACKLIST{
      "properties",      "items",    "optional",        "additionalProperties",
      "requires",        "minimum",  "maximum",         "minimumCanEqual",
      "maximumCanEqual", "minItems", "maxItems",        "maxLength",
      "minLength",       "format",   "contentEncoding", "maxDecimal"};
};
