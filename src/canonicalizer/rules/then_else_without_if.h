namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_superfluous
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/applicator | Y        |
///
/// Declaring either the `then` or `else` keywords from the Applicator
/// vocabulary without also declaring the `if` keyword from the Validation
/// vocabulary does not contribute any constraints to the given schema, and thus
/// can be removed.
///
/// \f[\frac{if \not\in dom(S) \land \{ then, else \} \cap dom(S) \neq \emptyset
/// }{S \mapsto S \setminus \{ then, else \}
/// }\f]

class ThenElseWithoutIf final : public sourcemeta::alterschema::Rule {
public:
  ThenElseWithoutIf() : Rule("then_else_without_if"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &draft,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return draft == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           !sourcemeta::jsontoolkit::defines(schema, "if") &&
           (sourcemeta::jsontoolkit::defines(schema, "then") ||
            sourcemeta::jsontoolkit::defines(schema, "else"));
  }

  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::erase(value, "then");
    sourcemeta::jsontoolkit::erase(value, "else");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
