namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_superfluous
class EmptyPatternProperties final : public sourcemeta::alterschema::Rule {
public:
  EmptyPatternProperties() : Rule("empty_pattern_properties"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &draft,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return draft == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           sourcemeta::jsontoolkit::defines(schema, "patternProperties") &&
           sourcemeta::jsontoolkit::is_object(
               sourcemeta::jsontoolkit::at(schema, "patternProperties")) &&
           sourcemeta::jsontoolkit::empty(
               sourcemeta::jsontoolkit::at(schema, "patternProperties"));
  }

  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::erase(value, "patternProperties");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
