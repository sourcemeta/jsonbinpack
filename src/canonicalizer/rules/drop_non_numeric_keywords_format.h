namespace sourcemeta::jsonbinpack::canonicalizer {

class DropNonNumericKeywordsFormat final
    : public sourcemeta::alterschema::Rule {
public:
  DropNonNumericKeywordsFormat() : Rule("drop_non_numeric_keywords_format"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::defines(schema, "type") &&
           sourcemeta::jsontoolkit::is_string(
               sourcemeta::jsontoolkit::at(schema, "type")) &&
           (sourcemeta::jsontoolkit::to_string(
                sourcemeta::jsontoolkit::at(schema, "type")) == "integer" ||
            sourcemeta::jsontoolkit::to_string(
                sourcemeta::jsontoolkit::at(schema, "type")) == "number") &&
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
