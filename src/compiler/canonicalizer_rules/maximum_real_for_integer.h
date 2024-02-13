/// @ingroup canonicalizer_rules_simplification
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// If the `type` keyword from the Validation vocabulary is set to `integer` and
/// the `maximum` keyword from the Validation vocabulary is set to a real
/// number, then the upper bound is the floor of such real number.
///
/// \f[\frac{S.type = integer \land maximum \in dom(S) \land S.maximum \in
/// \mathbb{R}}{S \mapsto S \cup \{ maximum \mapsto \lfloor S.maximum \rfloor \}
/// }\f]

class MaximumRealForInteger final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  MaximumRealForInteger() : SchemaTransformRule("maximum_real_for_integer"){};

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
           schema.defines("maximum") && schema.at("maximum").is_real();
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    const auto current{transformer.schema().at("maximum").to_real()};
    const auto new_value{static_cast<std::int64_t>(std::floor(current))};
    transformer.assign("maximum", sourcemeta::jsontoolkit::JSON{new_value});
  }
};
