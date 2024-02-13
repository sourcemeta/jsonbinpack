/// @ingroup canonicalizer_rules_simplification
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// The `required` keyword from the Validation vocabulary declares *which*
/// object properties must be present in the object instance. Similarly, the
/// `minProperties` keyword from the Validation vocabulary declares *how many*
/// properties must be present in the object instance. Therefore, assuming the
/// `required` keyword does not contain duplicates (as handled by @ref
/// sourcemeta::jsonbinpack::canonicalizer::DuplicateRequiredJSONs), the
/// integer in `minProperties` has to be at least equal to the length of the
/// `required` array.
///
/// \f[\frac{\{ required, minProperties \} \subseteq dom(S) \land \# S.required
/// > S.minProperties}{S \mapsto S \cup \{ minProperties \mapsto \#S.required \}
/// }\f]

class MinPropertiesRequiredTautology final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  MinPropertiesRequiredTautology()
      : SchemaTransformRule("min_properties_required_tautology"){};

  /// The rule condition
  [[nodiscard]] auto condition(const sourcemeta::jsontoolkit::JSON &schema,
                               const std::string &dialect,
                               const std::set<std::string> &vocabularies,
                               const sourcemeta::jsontoolkit::Pointer &) const
      -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.defines("minProperties") &&
           schema.at("minProperties").is_integer() &&
           schema.defines("required") && schema.at("required").is_array() &&
           is_unique(schema.at("required")) &&
           schema.at("required").size() >
               static_cast<std::uint64_t>(
                   schema.at("minProperties").to_integer());
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.assign("minProperties",
                       sourcemeta::jsontoolkit::JSON{
                           transformer.schema().at("required").size()});
  }
};
