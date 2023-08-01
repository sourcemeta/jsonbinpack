namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_simplification
class EqualNumericBoundsAsConst final : public sourcemeta::alterschema::Rule {
public:
  EqualNumericBoundsAsConst() : Rule("equal_numeric_bounds_as_const"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &draft,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return draft == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           sourcemeta::jsontoolkit::defines(schema, "minimum") &&
           sourcemeta::jsontoolkit::is_number(
               sourcemeta::jsontoolkit::at(schema, "minimum")) &&
           sourcemeta::jsontoolkit::defines(schema, "maximum") &&
           sourcemeta::jsontoolkit::is_number(
               sourcemeta::jsontoolkit::at(schema, "maximum")) &&
           sourcemeta::jsontoolkit::at(schema, "minimum") ==
               sourcemeta::jsontoolkit::at(schema, "maximum");
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::assign(
        document, value, "const",
        sourcemeta::jsontoolkit::at(value, "minimum"));
    sourcemeta::jsontoolkit::erase(value, "minimum");
    sourcemeta::jsontoolkit::erase(value, "maximum");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
