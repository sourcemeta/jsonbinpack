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

class ThenElseWithoutIf final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  ThenElseWithoutIf() : SchemaTransformRule("then_else_without_if"){};

  /// The rule condition
  [[nodiscard]] auto condition(const sourcemeta::jsontoolkit::JSON &schema,
                               const std::string &dialect,
                               const std::set<std::string> &vocabularies,
                               const sourcemeta::jsontoolkit::Pointer &) const
      -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           schema.is_object() && !schema.defines("if") &&
           (schema.defines("then") || schema.defines("else"));
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.erase("then");
    transformer.erase("else");
  }
};
