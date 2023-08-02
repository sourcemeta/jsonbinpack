namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_simplification
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// If the `type` keyword from the Validation vocabulary is set to either
/// `number` or `integer` and the `minimum` and `maximum` keywords from the
/// Validation keywords are set to the same number, then the only instance that
/// can possibly match the schema is such number.
///
/// \f[\frac{S.type \in \{ number, integer \} \land \{ minimum, maximum \}
/// \subseteq dom(S) \land S.minimum = S.maximum}{S \mapsto S \cup \{ const
/// \mapsto S.minimum \} \setminus \{ minimum, maximum \}
/// }\f]

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
           sourcemeta::jsontoolkit::defines(schema, "type") &&
           sourcemeta::jsontoolkit::is_string(
               sourcemeta::jsontoolkit::at(schema, "type")) &&
           (sourcemeta::jsontoolkit::to_string(
                sourcemeta::jsontoolkit::at(schema, "type")) == "integer" ||
            sourcemeta::jsontoolkit::to_string(
                sourcemeta::jsontoolkit::at(schema, "type")) == "number") &&
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
