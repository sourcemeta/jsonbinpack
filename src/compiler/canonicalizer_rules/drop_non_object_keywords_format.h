class DropNonObjectKeywordsFormat final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  DropNonObjectKeywordsFormat()
      : SchemaTransformRule("drop_non_object_keywords_format"){};

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
           (vocabularies.contains("https://json-schema.org/draft/2020-12/vocab/"
                                  "format-annotation") ||
            vocabularies.contains("https://json-schema.org/draft/2020-12/vocab/"
                                  "format-assertion")) &&
           schema.defines_any(this->BLACKLIST_FORMAT.cbegin(),
                              this->BLACKLIST_FORMAT.cend());
  }

  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.erase_keys(this->BLACKLIST_FORMAT.cbegin(),
                           this->BLACKLIST_FORMAT.cend());
  }

private:
  const std::set<std::string> BLACKLIST_FORMAT{"format"};
};
