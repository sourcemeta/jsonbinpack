namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_simplification
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// If the `type` keyword from the Validation vocabulary is set to `array` and
/// the `maxItems` keyword from the Validation is set to 0, then the only
/// instance that can possibly match the schema is the empty array.
///
/// \f[\frac{S.type = array \land S.maxItems = 0}{S
/// \mapsto S \cup \{ const \mapsto \langle\rangle \} \setminus \{ maxItems \}
/// }\f]

class EmptyArrayAsConst final : public sourcemeta::alterschema::Rule {
public:
  EmptyArrayAsConst() : Rule("empty_array_as_const"){};
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
           sourcemeta::jsontoolkit::to_string(
               sourcemeta::jsontoolkit::at(schema, "type")) == "array" &&
           sourcemeta::jsontoolkit::defines(schema, "maxItems") &&
           sourcemeta::jsontoolkit::is_integer(
               sourcemeta::jsontoolkit::at(schema, "maxItems")) &&
           sourcemeta::jsontoolkit::to_integer(
               sourcemeta::jsontoolkit::at(schema, "maxItems")) == 0;
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::assign(document, value, "const",
                                    sourcemeta::jsontoolkit::make_array());
    sourcemeta::jsontoolkit::erase(value, "maxItems");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
