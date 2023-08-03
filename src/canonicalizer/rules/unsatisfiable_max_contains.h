namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_superfluous
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// Declaring the `maxContains` keyword from the Validation vocabulary to a
/// value that is greater or equal to the value set in the `maxItems` keyword
/// from the Validation vocabulary does not contribute any constraints to the
/// given schema, as `maxContains` would never be unsuccessful.
///
/// \f[\frac{\{ maxContains, maxItems \} \subseteq dom(S) \land S.maxContains
/// \geq S.maxItems }{S \mapsto S \setminus \{ maxContains \} }\f]

class UnsatisfiableMaxContains final : public sourcemeta::alterschema::Rule {
public:
  UnsatisfiableMaxContains() : Rule("unsatisfiable_max_contains"){};

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
           sourcemeta::jsontoolkit::defines(schema, "maxContains") &&
           sourcemeta::jsontoolkit::is_integer(
               sourcemeta::jsontoolkit::at(schema, "maxContains")) &&
           sourcemeta::jsontoolkit::defines(schema, "maxItems") &&
           sourcemeta::jsontoolkit::is_integer(
               sourcemeta::jsontoolkit::at(schema, "maxItems")) &&
           sourcemeta::jsontoolkit::to_integer(
               sourcemeta::jsontoolkit::at(schema, "maxContains")) >=
               sourcemeta::jsontoolkit::to_integer(
                   sourcemeta::jsontoolkit::at(schema, "maxItems"));
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::erase(value, "maxContains");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
