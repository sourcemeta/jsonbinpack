namespace sourcemeta::jsonbinpack::canonicalizer {

class DropNonNullKeywordsApplicator final
    : public sourcemeta::alterschema::Rule {
public:
  DropNonNullKeywordsApplicator() : Rule("drop_non_null_keywords_applicator"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           is_null_schema(schema, vocabularies) &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           sourcemeta::jsontoolkit::defines_any(schema,
                                                this->BLACKLIST_APPLICATOR);
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::erase_many(value, this->BLACKLIST_APPLICATOR);
  }

private:
  const std::set<std::string> BLACKLIST_APPLICATOR{"properties",
                                                   "patternProperties",
                                                   "additionalProperties",
                                                   "dependentSchemas",
                                                   "propertyNames",
                                                   "prefixItems",
                                                   "contains",
                                                   "items"};
};
} // namespace sourcemeta::jsonbinpack::canonicalizer
