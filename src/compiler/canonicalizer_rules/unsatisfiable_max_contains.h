/// @ingroup canonicalizer_rules_superfluous
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// Declaring the `maxContains` keyword from the Validation vocabulary to a
/// value that is greater or equal to the value set in the `maxItems` keyword
/// from the Validation vocabulary does not contribute any constraints to the
/// given schema, as `maxContains` would never be unsuccessful.
///
/// \f[\frac{\{ maxContains, maxItems \} \subseteq dom(S) \land S.maxContains
/// \geq S.maxItems }{S \mapsto S \setminus \{ maxContains \} }\f]

class UnsatisfiableMaxContains final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  UnsatisfiableMaxContains()
      : SchemaTransformRule("unsatisfiable_max_contains"){};

  /// The rule condition
  [[nodiscard]] auto condition(const sourcemeta::jsontoolkit::JSON &schema,
                               const std::string &dialect,
                               const std::set<std::string> &vocabularies,
                               const sourcemeta::jsontoolkit::Pointer &) const
      -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.defines("maxContains") &&
           schema.at("maxContains").is_integer() &&
           schema.defines("maxItems") && schema.at("maxItems").is_integer() &&
           schema.at("maxContains").to_integer() >=
               schema.at("maxItems").to_integer();
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.erase("maxContains");
  }
};
