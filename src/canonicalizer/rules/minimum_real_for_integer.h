namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_simplification
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// If the `type` keyword from the Validation vocabulary is set to `integer` and
/// the `minimum` keyword from the Validation vocabulary is set to a real
/// number, then the lower bound is the ceil of such real number.
///
/// \f[\frac{S.type = integer \land minimum \in dom(S) \land S.minimum \in
/// \mathbb{R}}{S \mapsto S \cup \{ minimum \mapsto \lceil S.minimum \rceil \}
/// }\f]

class MinimumRealForInteger final : public sourcemeta::alterschema::Rule {
public:
  MinimumRealForInteger() : Rule("minimum_real_for_integer"){};
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
               sourcemeta::jsontoolkit::at(schema, "type")) == "integer" &&
           sourcemeta::jsontoolkit::defines(schema, "minimum") &&
           sourcemeta::jsontoolkit::is_real(
               sourcemeta::jsontoolkit::at(schema, "minimum"));
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    const auto current{sourcemeta::jsontoolkit::to_real(
        sourcemeta::jsontoolkit::at(value, "minimum"))};
    const auto new_value{static_cast<std::int64_t>(std::ceil(current))};
    sourcemeta::jsontoolkit::assign(document, value, "minimum",
                                    sourcemeta::jsontoolkit::from(new_value));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
