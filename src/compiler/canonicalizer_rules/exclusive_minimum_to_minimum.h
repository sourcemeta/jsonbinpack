namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_syntax_sugar
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// The constraint imposed by the `exclusiveMinimum` keyword from the Validation
/// vocabulary can be expressed in terms of the `minimum` keyword from the
/// Validation vocabulary.
///
/// \f[\frac{exclusiveMinimum \in dom(S) \land minimum \not\in dom(S)}{S \mapsto
/// S \cup \{ minimum \mapsto S.exclusiveMinimum + 1 \} \setminus \{
/// exclusiveMinimum \} }\f]

class ExclusiveMinimumToMinimum final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  ExclusiveMinimumToMinimum()
      : SchemaTransformRule("exclusive_minimum_to_minimum"){};

  /// The rule condition
  [[nodiscard]] auto condition(const sourcemeta::jsontoolkit::JSON &schema,
                               const std::string &dialect,
                               const std::set<std::string> &vocabularies,
                               const sourcemeta::jsontoolkit::Pointer &) const
      -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.defines("exclusiveMinimum") &&
           schema.at("exclusiveMinimum").is_number() &&
           !schema.defines("minimum");
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    auto new_minimum = transformer.schema().at("exclusiveMinimum");
    new_minimum += sourcemeta::jsontoolkit::JSON{1};
    transformer.assign("minimum", new_minimum);
    transformer.erase("exclusiveMinimum");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
