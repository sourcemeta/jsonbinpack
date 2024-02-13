/// @ingroup canonicalizer_rules_simplification
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// If the `type` keyword from the Validation vocabulary is set to `object` and
/// the `maxProperties` keyword from the Validation vocabulary is set to 0, then
/// the only instance that can possibly match the schema is the empty object.
///
/// \f[\frac{S.type = object \land S.maxProperties = 0}{S
/// \mapsto S \cup \{ const \mapsto \{\} \} \setminus \{ maxProperties \}
/// }\f]

class EmptyObjectAsConst final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  EmptyObjectAsConst() : SchemaTransformRule("empty_object_as_const"){};

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
           schema.defines("maxProperties") &&
           schema.at("maxProperties").is_integer() &&
           schema.at("maxProperties").to_integer() == 0;
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.assign("const", sourcemeta::jsontoolkit::JSON::make_object());
    transformer.erase("maxProperties");
  }
};
