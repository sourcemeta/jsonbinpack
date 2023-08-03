namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_implicit
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// If the `type` keyword from the Validation vocabulary is set to `object` but
/// the `required` keyword from the Validation vocabulary is omitted, the latter
/// defaults to the empty array.
///
/// \f[\frac{S.type = object \land required \not\in dom(S)}{S
/// \mapsto S \cup \{ required \mapsto \langle \rangle \}
/// }\f]

class ImplicitObjectRequired final : public sourcemeta::alterschema::Rule {
public:
  ImplicitObjectRequired() : Rule("implicit_object_required"){};

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
               sourcemeta::jsontoolkit::at(schema, "type")) == "object" &&
           !sourcemeta::jsontoolkit::defines(schema, "required");
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::assign(document, value, "required",
                                    sourcemeta::jsontoolkit::make_array());
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
