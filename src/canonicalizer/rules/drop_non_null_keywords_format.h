namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules
class DropNonNullKeywordsFormat final : public sourcemeta::alterschema::Rule {
public:
  DropNonNullKeywordsFormat() : Rule("drop_non_null_keywords_format"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           is_null_schema(schema, vocabularies) &&
           (vocabularies.contains("https://json-schema.org/draft/2020-12/vocab/"
                                  "format-annotation") ||
            vocabularies.contains("https://json-schema.org/draft/2020-12/vocab/"
                                  "format-assertion")) &&
           sourcemeta::jsontoolkit::defines_any(schema, this->BLACKLIST_FORMAT);
  }

  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::erase_many(value, this->BLACKLIST_FORMAT);
  }

private:
  const std::set<std::string> BLACKLIST_FORMAT{"format"};
};
} // namespace sourcemeta::jsonbinpack::canonicalizer
