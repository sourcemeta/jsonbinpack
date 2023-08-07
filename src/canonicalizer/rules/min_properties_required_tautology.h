namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_simplification
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// The `required` keyword from the Validation vocabulary declares *which*
/// object properties must be present in the object instance. Similarly, the
/// `minProperties` keyword from the Validation vocabulary declares *how many*
/// properties must be present in the object instance. Therefore, assuming the
/// `required` keyword does not contain duplicates (as handled by @ref
/// sourcemeta::jsonbinpack::canonicalizer::DuplicateRequiredValues), the
/// integer in `minProperties` has to be at least equal to the length of the
/// `required` array.
///
/// \f[\frac{\{ required, minProperties \} \subseteq dom(S) \land \# S.required
/// > S.minProperties}{S \mapsto S \cup \{ minProperties \mapsto \#S.required \}
/// }\f]

class MinPropertiesRequiredTautology final
    : public sourcemeta::alterschema::Rule {
public:
  MinPropertiesRequiredTautology()
      : Rule("min_properties_required_tautology"){};

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
           sourcemeta::jsontoolkit::defines(schema, "minProperties") &&
           sourcemeta::jsontoolkit::is_integer(
               sourcemeta::jsontoolkit::at(schema, "minProperties")) &&
           sourcemeta::jsontoolkit::defines(schema, "required") &&
           sourcemeta::jsontoolkit::is_array(
               sourcemeta::jsontoolkit::at(schema, "required")) &&
           is_unique(sourcemeta::jsontoolkit::at(schema, "required")) &&
           sourcemeta::jsontoolkit::size(
               sourcemeta::jsontoolkit::at(schema, "required")) >
               static_cast<std::uint64_t>(sourcemeta::jsontoolkit::to_integer(
                   sourcemeta::jsontoolkit::at(schema, "minProperties")));
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::assign(
        document, value, "minProperties",
        sourcemeta::jsontoolkit::from(sourcemeta::jsontoolkit::size(
            sourcemeta::jsontoolkit::at(value, "required"))));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
