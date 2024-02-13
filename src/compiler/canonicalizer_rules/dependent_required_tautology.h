class DependentRequiredTautology final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  DependentRequiredTautology()
      : SchemaTransformRule("dependent_required_tautology"){};

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
