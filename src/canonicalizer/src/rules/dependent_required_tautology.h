#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

#include <algorithm> // std::any_of, std::copy
#include <iterator>  // std::back_inserter
#include <vector>    // std::vector

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class DependentRequiredTautology final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  DependentRequiredTautology() : Rule("dependent_required_tautology"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema,
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.defines("dependentRequired") &&
           schema.at("dependentRequired").is_object() &&
           schema.defines("required") && schema.at("required").is_array() &&
           std::any_of(schema.at("required").to_array().cbegin(),
                       schema.at("required").to_array().cend(),
                       [&](const auto &element) {
                         return element.is_string() &&
                                schema.at("dependentRequired")
                                    .defines(element.to_string()) &&
                                schema.at("dependentRequired")
                                    .at(element.to_string())
                                    .is_array();
                       });
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    std::vector<sourcemeta::jsontoolkit::JSON<std::string>> new_requires{};

    for (const auto &element : schema.at("required").to_array()) {
      if (!element.is_string() ||
          !schema.at("dependentRequired").defines(element.to_string())) {
        continue;
      }

      const auto &dependent_requires =
          schema.at("dependentRequired").at(element.to_string()).to_array();
      std::copy(dependent_requires.cbegin(), dependent_requires.cend(),
                std::back_inserter(new_requires));
      schema.at("dependentRequired").erase(element.to_string());
    }

    for (auto &new_require : new_requires) {
      if (!schema.at("required").contains(new_require)) {
        schema.at("required").push_back(std::move(new_require));
      }
    }
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
