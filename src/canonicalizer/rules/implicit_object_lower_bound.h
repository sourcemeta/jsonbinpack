namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_implicit
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// JSON objects cannot have a negative number of properties. If the `type`
/// keyword from the Validation vocabulary is set to `object` and no lower bound
/// is set, the implicit lower bound is zero.
///
/// \f[\frac{S.type = object \land minProperties \not\in dom(S)}{S
/// \mapsto S \cup \{ minProperties \mapsto 0 \}
/// }\f]

class ImplicitObjectLowerBound final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  ImplicitObjectLowerBound()
      : SchemaTransformRule("implicit_object_lower_bound"){};

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
           schema.at("type").to_string() == "object" &&
           !schema.defines("minProperties");
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.assign("minProperties", sourcemeta::jsontoolkit::JSON{0});
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
