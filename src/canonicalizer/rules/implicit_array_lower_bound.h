namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_implicit
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// JSON arrays cannot have a negative number of elements. If the `type` keyword
/// from the Validation vocabulary is set to `array` and no lower bound is set,
/// the implicit lower bound is zero.
///
/// \f[\frac{S.type = array \land minItems \not\in dom(S)}{S
/// \mapsto S \cup \{ minItems \mapsto 0 \}
/// }\f]

class ImplicitArrayLowerBound final : public sourcemeta::alterschema::Rule {
public:
  ImplicitArrayLowerBound() : Rule("implicit_array_lower_bound"){};

  /// The rule condition
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
           !sourcemeta::jsontoolkit::defines(schema, "minItems");
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::assign(document, value, "minItems",
                                    sourcemeta::jsontoolkit::from(0));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
