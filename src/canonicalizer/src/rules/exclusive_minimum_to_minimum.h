#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

#include <algorithm> // std::max

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class ExclusiveMinimumToMinimum final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  ExclusiveMinimumToMinimum() : Rule("exclusive_minimum_to_minimum"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema,
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.contains("exclusiveMinimum") &&
           (schema.at("exclusiveMinimum").is_integer() ||
            schema.at("exclusiveMinimum").is_real());
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    if (schema.at("exclusiveMinimum").is_integer()) {
      const std::int64_t minimum =
          schema.at("exclusiveMinimum").to_integer() + 1;
      if (!schema.contains("minimum") ||
          (schema.at("minimum").is_real() &&
           static_cast<long double>(schema.at("minimum").to_real()) <
               minimum)) {
        schema.assign("minimum", minimum);
      } else if (schema.at("minimum").is_integer()) {
        schema.assign("minimum",
                      std::max(schema.at("minimum").to_integer(), minimum));
      }
    } else {
      const double minimum = schema.at("exclusiveMinimum").to_real() + 1.0;
      if (!schema.contains("minimum") ||
          (schema.at("minimum").is_integer() &&
           schema.at("minimum").to_integer() <
               static_cast<long double>(minimum))) {
        schema.assign("minimum", minimum);
      } else if (schema.at("minimum").is_real()) {
        schema.assign("minimum",
                      std::max(schema.at("minimum").to_real(), minimum));
      }
    }

    schema.erase("exclusiveMinimum");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
