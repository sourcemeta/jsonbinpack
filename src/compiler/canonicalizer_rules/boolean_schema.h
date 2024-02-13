/// @ingroup canonicalizer_rules_syntax_sugar
///
/// ### JSON Schema 2020-12
///
/// The [Core](https://json-schema.org/draft/2020-12/json-schema-core.html)
/// specification defines the trivial boolean schemas `true` and `false` where
/// `true` validates successfully against any instance and `false` never
/// validates successfully against any instance.  According to the
/// specification, boolean schemas are syntactic sugar for the empty object
/// schema and the `not` applicator.
///
/// For the `true` schema:
///
/// \f[\frac{S = true}{S \mapsto \{\}}\f]
///
/// For the `false` schema:
///
/// \f[\frac{S = false}{S \mapsto \{ not \mapsto \{\} \}}\f]

class BooleanSchema final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  BooleanSchema() : SchemaTransformRule("boolean_schema"){};

  /// The rule condition
  [[nodiscard]] auto condition(const sourcemeta::jsontoolkit::JSON &schema,
                               const std::string &,
                               const std::set<std::string> &,
                               const sourcemeta::jsontoolkit::Pointer &) const
      -> bool override {
    return schema.is_boolean();
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    const bool current_value{transformer.schema().to_boolean()};
    transformer.replace(sourcemeta::jsontoolkit::JSON::make_object());
    if (!current_value) {
      transformer.assign("not", sourcemeta::jsontoolkit::JSON::make_object());
    }
  }
};
