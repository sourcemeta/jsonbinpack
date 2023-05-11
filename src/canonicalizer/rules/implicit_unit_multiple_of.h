namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules
class ImplicitUnitMultipleOf final : public sourcemeta::alterschema::Rule {
public:
  ImplicitUnitMultipleOf() : Rule("implicit_unit_multiple_of"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           sourcemeta::jsontoolkit::defines(schema, "type") &&
           sourcemeta::jsontoolkit::is_string(
               sourcemeta::jsontoolkit::at(schema, "type")) &&
           sourcemeta::jsontoolkit::to_string(
               sourcemeta::jsontoolkit::at(schema, "type")) == "integer" &&
           !sourcemeta::jsontoolkit::defines(schema, "multipleOf");
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::assign(document, value, "multipleOf",
                                    sourcemeta::jsontoolkit::from(1));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
