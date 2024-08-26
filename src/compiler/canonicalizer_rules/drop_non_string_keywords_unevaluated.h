class DropNonStringKeywordsUnevaluated final
    : public sourcemeta::alterschema::Rule {
public:
  DropNonStringKeywordsUnevaluated()
      : Rule("drop_non_string_keywords_unevaluated") {};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON &schema,
            const std::string &dialect,
            const std::set<std::string> &vocabularies,
            const sourcemeta::jsontoolkit::Pointer &) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.defines("type") && schema.at("type").is_string() &&
           schema.at("type").to_string() == "string" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/unevaluated") &&
           schema.defines_any(this->BLACKLIST_UNEVALUATED.cbegin(),
                              this->BLACKLIST_UNEVALUATED.cend());
  }

  auto transform(sourcemeta::alterschema::Transformer &transformer) const
      -> void override {
    transformer.erase_keys(this->BLACKLIST_UNEVALUATED.cbegin(),
                           this->BLACKLIST_UNEVALUATED.cend());
  }

private:
  const std::set<std::string> BLACKLIST_UNEVALUATED{"unevaluatedItems",
                                                    "unevaluatedProperties"};
};
