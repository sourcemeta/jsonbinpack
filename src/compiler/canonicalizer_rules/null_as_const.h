/// @ingroup canonicalizer_rules_syntax_sugar
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// If the `type` keyword from the Validation vocabulary is set to `null`, the
/// only possible matching instance is the `null` value. As such, the same
/// constraint can be expressed using the `const` keyword.
///
/// \f[\frac{S.type = null}{S
/// \mapsto S \cup \{ const \mapsto null \} \setminus \{ type \}
/// }\f]

class NullAsConst final : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  NullAsConst() : SchemaTransformRule("null_as_const"){};

  /// The rule condition
  [[nodiscard]] auto condition(const sourcemeta::jsontoolkit::JSON &schema,
                               const std::string &dialect,
                               const std::set<std::string> &vocabularies,
                               const sourcemeta::jsontoolkit::Pointer &) const
      -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           schema.is_object() && schema.defines("type") &&
           schema.at("type").is_string() &&
           schema.at("type").to_string() == "null";
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.assign("const", sourcemeta::jsontoolkit::JSON{nullptr});
    transformer.erase("type");
  }
};
