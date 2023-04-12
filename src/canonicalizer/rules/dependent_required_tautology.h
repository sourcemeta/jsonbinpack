namespace sourcemeta::jsonbinpack::canonicalizer {

class DependentRequiredTautology final : public sourcemeta::alterschema::Rule {
public:
  DependentRequiredTautology() : Rule("dependent_required_tautology"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           sourcemeta::jsontoolkit::defines(schema, "dependentRequired") &&
           sourcemeta::jsontoolkit::is_object(
               sourcemeta::jsontoolkit::at(schema, "dependentRequired")) &&
           sourcemeta::jsontoolkit::defines(schema, "required") &&
           sourcemeta::jsontoolkit::is_array(
               sourcemeta::jsontoolkit::at(schema, "required")) &&
           std::any_of(
               sourcemeta::jsontoolkit::cbegin_array(
                   sourcemeta::jsontoolkit::at(schema, "required")),
               sourcemeta::jsontoolkit::cend_array(
                   sourcemeta::jsontoolkit::at(schema, "required")),
               [&schema](const auto &element) {
                 return sourcemeta::jsontoolkit::is_string(element) &&
                        sourcemeta::jsontoolkit::defines(
                            sourcemeta::jsontoolkit::at(schema,
                                                        "dependentRequired"),
                            sourcemeta::jsontoolkit::to_string(element));
               });
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    const auto &current_requirements{sourcemeta::jsontoolkit::from(
        sourcemeta::jsontoolkit::at(value, "required"))};

    for (const auto &element :
         sourcemeta::jsontoolkit::array_iterator(current_requirements)) {
      if (!sourcemeta::jsontoolkit::is_string(element)) {
        continue;
      }

      const auto name{sourcemeta::jsontoolkit::to_string(element)};
      if (!sourcemeta::jsontoolkit::defines(
              sourcemeta::jsontoolkit::at(value, "dependentRequired"), name)) {
        continue;
      }

      const auto &dependents{sourcemeta::jsontoolkit::at(
          sourcemeta::jsontoolkit::at(value, "dependentRequired"), name)};
      if (!sourcemeta::jsontoolkit::is_array(dependents)) {
        continue;
      }

      for (const auto &dependent :
           sourcemeta::jsontoolkit::array_iterator(dependents)) {
        if (!sourcemeta::jsontoolkit::is_string(dependent)) {
          continue;
        }

        if (!sourcemeta::jsontoolkit::contains(
                current_requirements,
                sourcemeta::jsontoolkit::from(dependent))) {
          sourcemeta::jsontoolkit::push_back(
              document, sourcemeta::jsontoolkit::at(value, "required"),
              sourcemeta::jsontoolkit::from(dependent));
        }
      }

      sourcemeta::jsontoolkit::erase(
          sourcemeta::jsontoolkit::at(value, "dependentRequired"), name);
    }
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
