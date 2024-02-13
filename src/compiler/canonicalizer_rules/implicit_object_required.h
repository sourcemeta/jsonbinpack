/// @ingroup canonicalizer_rules_implicit
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// If the `type` keyword from the Validation vocabulary is set to `object` but
/// the `required` keyword from the Validation vocabulary is omitted, the latter
/// defaults to the empty array.
///
/// \f[\frac{S.type = object \land required \not\in dom(S)}{S
/// \mapsto S \cup \{ required \mapsto \langle \rangle \}
/// }\f]

class ImplicitObjectRequired final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  ImplicitObjectRequired() : SchemaTransformRule("implicit_object_required"){};

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
           !schema.defines("required");
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.assign("required", sourcemeta::jsontoolkit::JSON::make_array());
  }
};
