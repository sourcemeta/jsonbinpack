/// @ingroup canonicalizer_rules_implicit
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// The integer 1 is the unit of multiplication for integers. If the `type`
/// keyword from the Validation vocabulary is set to `integer` and no multiplier
/// is set through the `multipleOf` keyword from the Validation vocabulary, the
/// multiplier is implicitly 1.
///
/// \f[\frac{S.type = integer \land multipleOf \not\in dom(S)}{S
/// \mapsto S \cup \{ multipleOf \mapsto 1 \}
/// }\f]

class ImplicitUnitMultipleOf final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  ImplicitUnitMultipleOf() : SchemaTransformRule("implicit_unit_multiple_of"){};

  /// The rule condition
  [[nodiscard]] auto condition(const sourcemeta::jsontoolkit::JSON &schema,
                               const std::string &dialect,
                               const std::set<std::string> &vocabularies,
                               const sourcemeta::jsontoolkit::Pointer &) const
      -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.defines("type") &&
           schema.at("type").is_string() &&
           schema.at("type").to_string() == "integer" &&
           !schema.defines("multipleOf");
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.assign("multipleOf", sourcemeta::jsontoolkit::JSON{1});
  }
};
