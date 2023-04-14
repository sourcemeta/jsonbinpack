namespace sourcemeta::jsonbinpack::canonicalizer {

class DropNonObjectKeywordsUnevaluated final
    : public sourcemeta::alterschema::Rule {
public:
  DropNonObjectKeywordsUnevaluated()
      : Rule("drop_non_object_keywords_unevaluated"){};
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
           sourcemeta::jsontoolkit::to_string(
               sourcemeta::jsontoolkit::at(schema, "type")) == "object" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/unevaluated") &&
           sourcemeta::jsontoolkit::defines_any(schema,
                                                this->BLACKLIST_UNEVALUATED);
  }

  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::erase_many(value, this->BLACKLIST_UNEVALUATED);
  }

private:
  const std::set<std::string> BLACKLIST_UNEVALUATED{"unevaluatedItems"};
};
} // namespace sourcemeta::jsonbinpack::canonicalizer
