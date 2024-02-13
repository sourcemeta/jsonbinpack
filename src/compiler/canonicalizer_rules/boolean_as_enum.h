/// @ingroup canonicalizer_rules_syntax_sugar
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// According to the JSON grammar, boolean values consist of two constants:
/// `false` and `true`. As such, setting the `type` JSON Schema keyword
/// from the Validation vocabulary to `boolean` is equivalent to explicitly
/// declaring the `enum` keyword from the Validation vocabulary to the
/// constants `false` and `true`.
///
/// \f[\frac{S.type = boolean}{S \mapsto S \cup \{ enum \mapsto \langle false,
/// true \rangle \} \setminus \{ type \} }\f]

class BooleanAsEnum final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  BooleanAsEnum() : SchemaTransformRule("boolean_as_enum"){};

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
           schema.at("type").to_string() == "boolean" &&
           !schema.defines("enum");
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    auto choices = sourcemeta::jsontoolkit::JSON::make_array();
    choices.push_back(sourcemeta::jsontoolkit::JSON{false});
    choices.push_back(sourcemeta::jsontoolkit::JSON{true});
    transformer.assign("enum", choices);
    transformer.erase("type");
  }
};
