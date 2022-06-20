#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

#include <algorithm> // std::min

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class ExclusiveMaximumToMaximum final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  ExclusiveMaximumToMaximum() : Rule("exclusive_maximum_to_maximum"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema,
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.defines("exclusiveMaximum") &&
           (schema.at("exclusiveMaximum").is_integer() ||
            schema.at("exclusiveMaximum").is_real());
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    if (schema.at("exclusiveMaximum").is_integer()) {
      const std::int64_t maximum =
          schema.at("exclusiveMaximum").to_integer() - 1;
      if (!schema.defines("maximum") ||
          (schema.at("maximum").is_real() &&

           static_cast<long double>(schema.at("maximum").to_real()) >
               maximum)) {
        schema.assign("maximum", maximum);
      } else if (schema.at("maximum").is_integer()) {
        schema.assign("maximum",
                      std::min(schema.at("maximum").to_integer(), maximum));
      }
    } else {
      const double maximum = schema.at("exclusiveMaximum").to_real() - 1.0;
      if (!schema.defines("maximum") ||
          (schema.at("maximum").is_integer() &&
           schema.at("maximum").to_integer() >
               static_cast<long double>(maximum))) {
        schema.assign("maximum", maximum);
      } else if (schema.at("maximum").is_real()) {
        schema.assign("maximum",
                      std::min(schema.at("maximum").to_real(), maximum));
      }
    }

    schema.erase("exclusiveMaximum");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
