namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_syntax_sugar
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// The constraint imposed by the `exclusiveMaximum` keyword from the Validation
/// vocabulary can be expressed in terms of the `maximum` keyword from the
/// Validation vocabulary.
///
/// \f[\frac{exclusiveMaximum \in dom(S) \land maximum \not\in dom(S)}{S \mapsto
/// S \cup \{ maximum \mapsto S.exclusiveMaximum - 1 \} \setminus \{
/// exclusiveMaximum \} }\f]

class ExclusiveMaximumToMaximum final : public sourcemeta::alterschema::Rule {
public:
  ExclusiveMaximumToMaximum() : Rule("exclusive_maximum_to_maximum"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &draft,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return draft == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           sourcemeta::jsontoolkit::defines(schema, "exclusiveMaximum") &&
           sourcemeta::jsontoolkit::is_number(
               sourcemeta::jsontoolkit::at(schema, "exclusiveMaximum")) &&
           !sourcemeta::jsontoolkit::defines(schema, "maximum");
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    auto new_maximum{sourcemeta::jsontoolkit::from(
        sourcemeta::jsontoolkit::at(value, "exclusiveMaximum"))};
    sourcemeta::jsontoolkit::add(new_maximum,
                                 sourcemeta::jsontoolkit::from(-1));
    sourcemeta::jsontoolkit::assign(document, value, "maximum", new_maximum);
    sourcemeta::jsontoolkit::erase(value, "exclusiveMaximum");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
