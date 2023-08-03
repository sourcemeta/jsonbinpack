namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_superfluous
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/applicator | Y        |
///
/// Declaring the `if` keyword from the Applicator vocabulary without also
/// declaring either the `then` or `else` keywords from the Validation
/// vocabulary does not contribute any constraints to the given schema, and thus
/// can be removed.
///
/// Note that dropping `if`, even if the other related keywords are not used,
/// results in potential dropped annotations.  However, this is fine in the
/// context of JSON BinPack, as it does not rely on these type of annotations.
///
/// \f[\frac{if \in dom(S) \land \{ then, else \} \cap dom(S) = \emptyset }{S
/// \mapsto S \setminus \{ if \}
/// }\f]

class IfWithoutThenElse final : public sourcemeta::alterschema::Rule {
public:
  IfWithoutThenElse() : Rule("if_without_then_else"){};

  /// The rule condition
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &draft,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return draft == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           sourcemeta::jsontoolkit::defines(schema, "if") &&
           !sourcemeta::jsontoolkit::defines(schema, "then") &&
           !sourcemeta::jsontoolkit::defines(schema, "else");
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::erase(value, "if");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
