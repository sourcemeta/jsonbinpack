/// @ingroup canonicalizer_rules_superfluous
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// Setting the `dependentRequired` keyword from the Validation vocabulary to
/// the empty object does not contribute any constraints to the given schema,
/// and thus can be removed.
///
/// \f[\frac{dependentRequired \in dom(S) \land \#S.dependentRequired = 0}{S
/// \mapsto S \setminus \{ dependentRequired \}
/// }\f]

class EmptyDependentRequired final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  EmptyDependentRequired() : SchemaTransformRule("empty_dependent_required"){};

  /// The rule condition
  [[nodiscard]] auto condition(const sourcemeta::jsontoolkit::JSON &schema,
                               const std::string &dialect,
                               const std::set<std::string> &vocabularies,
                               const sourcemeta::jsontoolkit::Pointer &) const
      -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.defines("dependentRequired") &&
           schema.at("dependentRequired").is_object() &&
           schema.at("dependentRequired").empty();
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.erase("dependentRequired");
  }
};
