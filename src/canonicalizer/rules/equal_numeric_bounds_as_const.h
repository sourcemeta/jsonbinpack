namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_simplification
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// If the `type` keyword from the Validation vocabulary is set to either
/// `number` or `integer` and the `minimum` and `maximum` keywords from the
/// Validation keywords are set to the same number, then the only instance that
/// can possibly match the schema is such number.
///
/// \f[\frac{S.type \in \{ number, integer \} \land \{ minimum, maximum \}
/// \subseteq dom(S) \land S.minimum = S.maximum}{S \mapsto S \cup \{ const
/// \mapsto S.minimum \} \setminus \{ minimum, maximum \}
/// }\f]

class EqualNumericBoundsAsConst final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  EqualNumericBoundsAsConst()
      : SchemaTransformRule("equal_numeric_bounds_as_const"){};

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
           (schema.at("type").to_string() == "integer" ||
            schema.at("type").to_string() == "number") &&
           schema.defines("minimum") && schema.at("minimum").is_number() &&
           schema.defines("maximum") && schema.at("maximum").is_number() &&
           schema.at("minimum") == schema.at("maximum");
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.assign("const", transformer.schema().at("minimum"));
    transformer.erase("minimum");
    transformer.erase("maximum");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
