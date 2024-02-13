class DropNonObjectKeywordsContent final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  DropNonObjectKeywordsContent()
      : SchemaTransformRule("drop_non_object_keywords_content"){};

  [[nodiscard]] auto condition(const sourcemeta::jsontoolkit::JSON &schema,
                               const std::string &dialect,
                               const std::set<std::string> &vocabularies,
                               const sourcemeta::jsontoolkit::Pointer &) const
      -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.defines("type") && schema.at("type").is_string() &&
           schema.at("type").to_string() == "object" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/content") &&
           schema.defines_any(this->BLACKLIST_CONTENT.cbegin(),
                              this->BLACKLIST_CONTENT.cend());
  }

  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.erase_keys(this->BLACKLIST_CONTENT.cbegin(),
                           this->BLACKLIST_CONTENT.cend());
  }

private:
  const std::set<std::string> BLACKLIST_CONTENT{
      "contentEncoding", "contentMediaType", "contentSchema"};
};
