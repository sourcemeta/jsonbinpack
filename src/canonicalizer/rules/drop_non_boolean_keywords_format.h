namespace sourcemeta::jsonbinpack::canonicalizer {

class DropNonBooleanKeywordsFormat final
    : public sourcemeta::alterschema::Rule {
public:
  DropNonBooleanKeywordsFormat() : Rule("drop_non_boolean_keywords_format"){};
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

    return (vocabularies.contains("https://json-schema.org/draft/2020-12/vocab/"
                                  "format-annotation") ||
            vocabularies.contains("https://json-schema.org/draft/2020-12/vocab/"
                                  "format-assertion")) &&
           sourcemeta::jsontoolkit::defines_any(schema, this->BLACKLIST_FORMAT);
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::erase_many(value, this->BLACKLIST_FORMAT);
  }

private:
  const std::set<std::string> BLACKLIST_FORMAT{"format"};
};
} // namespace sourcemeta::jsonbinpack::canonicalizer
