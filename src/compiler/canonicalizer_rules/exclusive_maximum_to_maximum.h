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

class ExclusiveMaximumToMaximum final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  ExclusiveMaximumToMaximum()
      : SchemaTransformRule("exclusive_maximum_to_maximum"){};

  /// The rule condition
  [[nodiscard]] auto condition(const sourcemeta::jsontoolkit::JSON &schema,
                               const std::string &dialect,
                               const std::set<std::string> &vocabularies,
                               const sourcemeta::jsontoolkit::Pointer &) const
      -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.defines("exclusiveMaximum") &&
           schema.at("exclusiveMaximum").is_number() &&
           !schema.defines("maximum");
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    auto new_maximum = transformer.schema().at("exclusiveMaximum");
    new_maximum += sourcemeta::jsontoolkit::JSON{-1};
    transformer.assign("maximum", new_maximum);
    transformer.erase("exclusiveMaximum");
  }
};
