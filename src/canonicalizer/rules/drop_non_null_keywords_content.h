namespace sourcemeta::jsonbinpack::canonicalizer {

class DropNonNullKeywordsContent final : public sourcemeta::alterschema::Rule {
public:
  DropNonNullKeywordsContent() : Rule("drop_non_null_keywords_content"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           is_null_schema(schema, vocabularies) &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/content") &&
           sourcemeta::jsontoolkit::defines_any(schema,
                                                this->BLACKLIST_CONTENT);
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::erase_many(value, this->BLACKLIST_CONTENT);
  }

private:
  const std::set<std::string> BLACKLIST_CONTENT{
      "contentEncoding", "contentMediaType", "contentSchema"};
};
} // namespace sourcemeta::jsonbinpack::canonicalizer
