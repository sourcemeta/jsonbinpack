class DropNonNullKeywordsUnevaluated final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  DropNonNullKeywordsUnevaluated()
      : SchemaTransformRule("drop_non_null_keywords_unevaluated"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON &schema,
            const std::string &dialect,
            const std::set<std::string> &vocabularies,
            const sourcemeta::jsontoolkit::Pointer &) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           is_null_schema(schema, vocabularies) &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/unevaluated") &&
           schema.defines_any(this->BLACKLIST_UNEVALUATED.cbegin(),
                              this->BLACKLIST_UNEVALUATED.cend());
  }

  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.erase_keys(this->BLACKLIST_UNEVALUATED.cbegin(),
                           this->BLACKLIST_UNEVALUATED.cend());
  }

private:
  const std::set<std::string> BLACKLIST_UNEVALUATED{"unevaluatedItems",
                                                    "unevaluatedProperties"};
};
