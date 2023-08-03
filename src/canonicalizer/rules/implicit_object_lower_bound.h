namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_implicit
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// JSON objects cannot have a negative number of properties. If the `type`
/// keyword from the Validation vocabulary is set to `object` and no lower bound
/// is set, the implicit lower bound is zero.
///
/// \f[\frac{S.type = object \land minProperties \not\in dom(S)}{S
/// \mapsto S \cup \{ minProperties \mapsto 0 \}
/// }\f]

class ImplicitObjectLowerBound final : public sourcemeta::alterschema::Rule {
public:
  ImplicitObjectLowerBound() : Rule("implicit_object_lower_bound"){};
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
               sourcemeta::jsontoolkit::at(schema, "type")) == "object" &&
           !sourcemeta::jsontoolkit::defines(schema, "minProperties");
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::assign(document, value, "minProperties",
                                    sourcemeta::jsontoolkit::from(0));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
