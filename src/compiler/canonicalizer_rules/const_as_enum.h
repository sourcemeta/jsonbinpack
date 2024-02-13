/// @ingroup canonicalizer_rules_syntax_sugar
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// The JSON Schema Validation vocabulary defines the `enum` keyword to
/// declare a set of matching values and the `const` keyword to define
/// a single matching value. As such, `const` is an enumeration consisting
/// of a single value.
///
/// \f[\frac{const \in dom(S)}{S \mapsto S \cup \{ enum \mapsto \langle S.const
/// \rangle \} \setminus \{const\} }\f]

class ConstAsEnum final : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  ConstAsEnum() : SchemaTransformRule("const_as_enum"){};

  /// The rule condition
  [[nodiscard]] auto condition(const sourcemeta::jsontoolkit::JSON &schema,
                               const std::string &dialect,
                               const std::set<std::string> &vocabularies,
                               const sourcemeta::jsontoolkit::Pointer &) const
      -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.defines("const");
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    sourcemeta::jsontoolkit::JSON values =
        sourcemeta::jsontoolkit::JSON::make_array();
    values.push_back(transformer.schema().at("const"));
    transformer.assign("enum", values);
    transformer.erase("const");
  }
};
