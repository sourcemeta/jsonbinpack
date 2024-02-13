/// @ingroup canonicalizer_rules_implicit
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// JSON strings cannot have a negative number of characters. If the `type`
/// keyword from the Validation vocabulary is set to `string` and no lower bound
/// is set, the implicit lower bound is zero.
///
/// \f[\frac{S.type = string \land minLength \not\in dom(S)}{S
/// \mapsto S \cup \{ minLength \mapsto 0 \}
/// }\f]

class ImplicitStringLowerBound final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  ImplicitStringLowerBound()
      : SchemaTransformRule("implicit_string_lower_bound"){};

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
           schema.at("type").to_string() == "string" &&
           !schema.defines("minLength");
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.assign("minLength", sourcemeta::jsontoolkit::JSON{0});
  }
};
