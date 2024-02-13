/// @ingroup canonicalizer_rules_superfluous
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/applicator | Y        |
///
/// Setting the `patternProperties` keyword from the Applicator vocabulary to
/// the empty object does not contribute any constraints to the given schema,
/// and thus can be removed.
///
/// \f[\frac{patternProperties \in dom(S) \land \#S.patternProperties = 0}{S
/// \mapsto S \setminus \{ patternProperties \}
/// }\f]

class EmptyPatternProperties final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  EmptyPatternProperties() : SchemaTransformRule("empty_pattern_properties"){};

  /// The rule condition
  [[nodiscard]] auto condition(const sourcemeta::jsontoolkit::JSON &schema,
                               const std::string &dialect,
                               const std::set<std::string> &vocabularies,
                               const sourcemeta::jsontoolkit::Pointer &) const
      -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           schema.is_object() && schema.defines("patternProperties") &&
           schema.at("patternProperties").is_object() &&
           schema.at("patternProperties").empty();
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.erase("patternProperties");
  }
};
