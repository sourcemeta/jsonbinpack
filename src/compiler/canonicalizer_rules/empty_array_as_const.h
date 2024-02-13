/// @ingroup canonicalizer_rules_simplification
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// If the `type` keyword from the Validation vocabulary is set to `array` and
/// the `maxItems` keyword from the Validation vocabulary is set to 0, then the
/// only instance that can possibly match the schema is the empty array.
///
/// \f[\frac{S.type = array \land S.maxItems = 0}{S
/// \mapsto S \cup \{ const \mapsto \langle\rangle \} \setminus \{ maxItems \}
/// }\f]

class EmptyArrayAsConst final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  EmptyArrayAsConst() : SchemaTransformRule("empty_array_as_const"){};

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
           schema.at("type").to_string() == "array" &&
           schema.defines("maxItems") && schema.at("maxItems").is_integer() &&
           schema.at("maxItems").to_integer() == 0;
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.assign("const", sourcemeta::jsontoolkit::JSON::make_array());
    transformer.erase("maxItems");
  }
};
