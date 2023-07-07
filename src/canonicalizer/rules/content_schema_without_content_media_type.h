namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules
class ContentSchemaWithoutContentMediaType final
    : public sourcemeta::alterschema::Rule {
public:
  ContentSchemaWithoutContentMediaType()
      : Rule("content_schema_without_content_media_type"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &draft,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return draft == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/content") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           sourcemeta::jsontoolkit::defines(schema, "contentSchema") &&
           !sourcemeta::jsontoolkit::defines(schema, "contentMediaType");
  }

  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::erase(value, "contentSchema");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
