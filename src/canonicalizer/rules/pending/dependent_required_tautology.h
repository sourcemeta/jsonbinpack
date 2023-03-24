namespace sourcemeta::jsonbinpack::canonicalizer {

class DependentRequiredTautology final : public sourcemeta::alterschema::Rule {
public:
  DependentRequiredTautology() : Rule("dependent_required_tautology"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary(
               schema, vocabularies::validation) &&
           schema.is_object() &&
           schema.defines(keywords::validation::dependentRequired) &&
           schema.at(keywords::validation::dependentRequired).is_object() &&
           schema.defines(keywords::validation::required) &&
           schema.at(keywords::validation::required).is_array() &&
           std::any_of(
               schema.at(keywords::validation::required).to_array().cbegin(),
               schema.at(keywords::validation::required).to_array().cend(),
               [&schema](const auto &element) {
                 return element.is_string() &&
                        schema.at(keywords::validation::dependentRequired)
                            .defines(element.to_string()) &&
                        schema.at(keywords::validation::dependentRequired)
                            .at(element.to_string())
                            .is_array();
               });
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    std::vector<sourcemeta::jsontoolkit::JSON<std::string>> new_requires{};

    for (const auto &element :
         schema.at(keywords::validation::required).to_array()) {
      if (!element.is_string() ||
          !schema.at(keywords::validation::dependentRequired)
               .defines(element.to_string())) {
        continue;
      }

      auto &dependent_requires =
          schema.at(keywords::validation::dependentRequired)
              .at(element.to_string())
              .to_array();
      std::copy(dependent_requires.begin(), dependent_requires.end(),
                std::back_inserter(new_requires));
      schema.at(keywords::validation::dependentRequired)
          .erase(element.to_string());
    }

    for (auto &new_require : new_requires) {
      if (!schema.at(keywords::validation::required).contains(new_require)) {
        schema.at(keywords::validation::required)
            .push_back(std::move(new_require));
      }
    }
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
