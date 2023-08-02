namespace sourcemeta::jsonbinpack::canonicalizer {

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

class BooleanSchema final : public sourcemeta::alterschema::Rule {
public:
  BooleanSchema() : Rule("boolean_schema"){};

  [[nodiscard]] auto condition(const sourcemeta::jsontoolkit::Value &schema,
                               const std::string &,
                               const std::unordered_map<std::string, bool> &,
                               const std::size_t) const -> bool override {
    return sourcemeta::jsontoolkit::is_boolean(schema);
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    const bool current_value{sourcemeta::jsontoolkit::to_boolean(value)};
    sourcemeta::jsontoolkit::make_object(value);
    if (!current_value) {
      sourcemeta::jsontoolkit::assign(document, value, "not",
                                      sourcemeta::jsontoolkit::make_object());
    }
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
