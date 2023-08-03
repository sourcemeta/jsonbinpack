namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_implicit
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// JSON strings cannot have a negative number of characters. If the `type`
/// keyword from the Validation vocabulary is set to `string` and no lower bound
/// is set, the implicit lower bound is zero.
///
/// \f[\frac{S.type = string \land minLength \not\in dom(S)}{S
/// \mapsto S \cup \{ minLength \mapsto 0 \}
/// }\f]

class ImplicitStringLowerBound final : public sourcemeta::alterschema::Rule {
public:
  ImplicitStringLowerBound() : Rule("implicit_string_lower_bound"){};
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
               sourcemeta::jsontoolkit::at(schema, "type")) == "string" &&
           !sourcemeta::jsontoolkit::defines(schema, "minLength");
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::assign(document, value, "minLength",
                                    sourcemeta::jsontoolkit::from(0));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
