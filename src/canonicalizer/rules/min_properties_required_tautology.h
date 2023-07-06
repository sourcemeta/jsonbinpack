namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules
class MinPropertiesRequiredTautology final
    : public sourcemeta::alterschema::Rule {
public:
  MinPropertiesRequiredTautology()
      : Rule("min_properties_required_tautology"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &draft,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return draft == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           sourcemeta::jsontoolkit::defines(schema, "minProperties") &&
           sourcemeta::jsontoolkit::is_integer(
               sourcemeta::jsontoolkit::at(schema, "minProperties")) &&
           sourcemeta::jsontoolkit::defines(schema, "required") &&
           sourcemeta::jsontoolkit::is_array(
               sourcemeta::jsontoolkit::at(schema, "required")) &&
           sourcemeta::jsontoolkit::size(
               sourcemeta::jsontoolkit::at(schema, "required")) >
               static_cast<std::uint64_t>(sourcemeta::jsontoolkit::to_integer(
                   sourcemeta::jsontoolkit::at(schema, "minProperties")));
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::assign(
        document, value, "minProperties",
        sourcemeta::jsontoolkit::from(sourcemeta::jsontoolkit::size(
            sourcemeta::jsontoolkit::at(value, "required"))));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
