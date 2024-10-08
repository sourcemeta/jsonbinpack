class DropNonNumericKeywords_Draft0 final : public Rule {
public:
  DropNonNumericKeywords_Draft0()
      : Rule{"drop_non_numeric_keywords_draft0",
             "Keywords that don't apply to numbers will never match if the "
             "instance is guaranteed to be a number"} {};

  [[nodiscard]] auto condition(const sourcemeta::jsontoolkit::JSON &schema,
                               const std::string &,
                               const std::set<std::string> &vocabularies,
                               const sourcemeta::jsontoolkit::Pointer &) const
      -> bool override {
    return vocabularies.contains(
               "http://json-schema.org/draft-00/hyper-schema#") &&
           schema.is_object() && schema.defines("type") &&
           schema.at("type").is_string() &&
           (schema.at("type").to_string() == "number" ||
            schema.at("type").to_string() == "integer") &&
           schema.defines_any(this->BLACKLIST.cbegin(), this->BLACKLIST.cend());
  }

  auto transform(Transformer &transformer) const -> void override {
    transformer.erase_keys(this->BLACKLIST.cbegin(), this->BLACKLIST.cend());
  }

private:
  const std::set<std::string> BLACKLIST{
      "properties", "items",    "optional",       "additionalProperties",
      "requires",   "minItems", "maxItems",       "maxLength",
      "minLength",  "format",   "contentEncoding"};
};
