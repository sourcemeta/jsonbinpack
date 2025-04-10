class DropNonBooleanKeywordsFormat_2019_09 final : public SchemaTransformRule {
public:
  DropNonBooleanKeywordsFormat_2019_09()
      : SchemaTransformRule{
            "drop_non_boolean_keywords_format_2019_09",
            "Keywords that don't apply to booleans will never match if the "
            "instance is guaranteed to be a boolean"} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::core::Vocabularies &vocabularies,
            const sourcemeta::core::SchemaFrame &,
            const sourcemeta::core::SchemaFrame::Location &,
            const sourcemeta::core::SchemaWalker &,
            const sourcemeta::core::SchemaResolver &) const -> bool override {
    return vocabularies.contains(
               "https://json-schema.org/draft/2019-09/vocab/validation") &&
           schema.is_object() &&
           ((schema.defines("type") && schema.at("type").is_string() &&
             schema.at("type").to_string() == "boolean") ||
            (schema.defines("enum") && schema.at("enum").is_array() &&
             every_item_is_boolean(schema.at("enum").as_array()))) &&
           vocabularies.contains(
               "https://json-schema.org/draft/2019-09/vocab/format") &&
           schema.defines_any(this->BLACKLIST.cbegin(), this->BLACKLIST.cend());
  }

  auto transform(JSON &schema) const -> void override {
    schema.erase_keys(this->BLACKLIST.cbegin(), this->BLACKLIST.cend());
  }

private:
  const std::set<std::string> BLACKLIST{"format"};
};
