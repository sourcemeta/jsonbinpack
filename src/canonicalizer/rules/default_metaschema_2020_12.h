namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_implicit
class DefaultMetaschema_2020_12 final : public sourcemeta::alterschema::Rule {
public:
  DefaultMetaschema_2020_12() : Rule("default_metaschema_2020_12"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &draft,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t level) const -> bool override {
    return draft == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/core") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           !sourcemeta::jsontoolkit::defines(schema, "$schema") && level == 0;
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::assign(
        document, value, "$schema",
        sourcemeta::jsontoolkit::from(
            "https://json-schema.org/draft/2020-12/schema"));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
