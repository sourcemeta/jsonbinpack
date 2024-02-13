/// @ingroup canonicalizer_rules_simplification
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// The `required` keyword from the Validation vocabulary declares which object
/// properties must be present in the given JSON object. The `dependentRequired`
/// keyword from the Validation vocabulary expresses that certain properties
/// are required based on whether other properties from the same object are
/// required or not. Therefore, if a property is required based on the presence
/// of another keyword that is ensured to be required, then the requirement
/// dependency can be elevated as an unconditional requirement.
///
/// \f[\frac{\{ required, dependentRequired \} \subseteq S \land S.required \cap
/// S.dependentRequired \neq \emptyset}{S \mapsto S \cup \{ dependentRequired
/// \mapsto D, required \mapsto R \} }\f]
///
/// Where:
///
/// \f[D = \{ (k, v) \in S.dependentRequired \mid k \not\in S.required \}\f]
///
/// \f[R = \bigcup \{ v \mid (k, v) \in S.dependentRequired \land k \in
/// S.required \}\f]

class DependentRequiredTautology final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  DependentRequiredTautology()
      : SchemaTransformRule("dependent_required_tautology"){};

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
           schema.defines("required") && schema.at("required").is_array() &&
           std::any_of(schema.at("required").as_array().cbegin(),
                       schema.at("required").as_array().cend(),
                       [&schema](const auto &element) {
                         return element.is_string() &&
                                schema.at("dependentRequired")
                                    .defines(element.to_string());
                       });
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    const auto &current_requirements = transformer.schema().at("required");
    sourcemeta::jsontoolkit::JSON new_requirements = current_requirements;

    for (const auto &element : current_requirements.as_array()) {
      if (!element.is_string()) {
        continue;
      }

      const auto name{element.to_string()};
      if (!transformer.schema().at("dependentRequired").defines(name)) {
        continue;
      }

      const auto &dependents{
          transformer.schema().at("dependentRequired").at(name)};
      if (!dependents.is_array()) {
        continue;
      }

      for (const auto &dependent : dependents.as_array()) {
        if (!dependent.is_string()) {
          continue;
        }

        if (!new_requirements.contains(dependent)) {
          new_requirements.push_back(dependent);
        }
      }

      transformer.erase({"dependentRequired"}, name);
    }

    transformer.assign("required", new_requirements);
  }
};
