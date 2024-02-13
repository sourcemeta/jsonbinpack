/// @ingroup canonicalizer_rules_simplification
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// If the `type` keyword from the Validation vocabulary is set to `string` and
/// the `maxLength` keyword from the Validation keyword is set to 0, then the
/// only instance that can possibly match the schema is the empty string.
///
/// \f[\frac{S.type = string \land S.maxLength = 0}{S
/// \mapsto S \cup \{ const \mapsto "" \} \setminus \{ maxLength \}
/// }\f]

class EmptyStringAsConst final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  EmptyStringAsConst() : SchemaTransformRule("empty_string_as_const"){};

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
           schema.defines("maxLength") && schema.at("maxLength").is_integer() &&
           schema.at("maxLength").to_integer() == 0;
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.assign("const", sourcemeta::jsontoolkit::JSON{""});
    transformer.erase("maxLength");
  }
};
