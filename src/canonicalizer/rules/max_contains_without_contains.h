namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_superfluous
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/applicator | Y        |
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// Declaring the `maxContains` keyword from the Validation
/// vocabulary without also declaring the `contains` keyword from the Applicator
/// vocabulary does not contribute any constraints to the given schema, and thus
/// can be removed.
///
/// \f[\frac{maxContains \in dom(S) \land contains \not\in dom(S) }{S \mapsto S
/// \setminus \{ maxContains \} }\f]

class MaxContainsWithoutContains final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  MaxContainsWithoutContains()
      : SchemaTransformRule("max_contains_without_contains"){};

  /// The rule condition
  [[nodiscard]] auto condition(const sourcemeta::jsontoolkit::JSON &schema,
                               const std::string &dialect,
                               const std::set<std::string> &vocabularies,
                               const sourcemeta::jsontoolkit::Pointer &) const
      -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.defines("maxContains") &&
           !schema.defines("contains");
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.erase("maxContains");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
