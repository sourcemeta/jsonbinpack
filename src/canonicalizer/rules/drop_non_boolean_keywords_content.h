namespace sourcemeta::jsonbinpack::canonicalizer {

class DropNonBooleanKeywordsContent final
    : public sourcemeta::alterschema::Rule {
public:
  DropNonBooleanKeywordsContent() : Rule("drop_non_boolean_keywords_content"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    if (dialect != "https://json-schema.org/draft/2020-12/schema" ||
        !sourcemeta::jsontoolkit::is_object(schema) ||
        !is_boolean_schema(schema, vocabularies)) {
      return false;
    }

    return vocabularies.contains(
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
