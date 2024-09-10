class ExclusiveMaximumIntegerToMaximum final : public Rule {
public:
  ExclusiveMaximumIntegerToMaximum()
      : Rule("exclusive_maximum_integer_to_maximum",
             "Setting `exclusiveMaximum` when `type` is `integer` is syntax "
             "sugar for `maximum`") {};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON &schema, const std::string &,
            const std::set<std::string> &vocabularies,
            const sourcemeta::jsontoolkit::Pointer &) const -> bool override {
    return contains_any(
               vocabularies,
               {"https://json-schema.org/draft/2020-12/vocab/validation",
                "https://json-schema.org/draft/2019-09/vocab/validation",
                "http://json-schema.org/draft-07/schema#",
                "http://json-schema.org/draft-06/schema#"}) &&
           schema.is_object() && schema.defines("type") &&
           schema.at("type").is_string() &&
           schema.at("type").to_string() == "integer" &&
           schema.defines("exclusiveMaximum") &&
           schema.at("exclusiveMaximum").is_number() &&
           !schema.defines("maximum");
  }

  auto transform(Transformer &transformer) const -> void override {
    if (transformer.schema().at("exclusiveMaximum").is_integer()) {
      auto new_maximum = transformer.schema().at("exclusiveMaximum");
      new_maximum += sourcemeta::jsontoolkit::JSON{-1};
      transformer.assign("maximum", new_maximum);
      transformer.erase("exclusiveMaximum");
    } else {
      const auto current{transformer.schema().at("exclusiveMaximum").to_real()};
      const auto new_value{static_cast<std::int64_t>(std::floor(current))};
      transformer.assign("maximum", sourcemeta::jsontoolkit::JSON{new_value});
      transformer.erase("exclusiveMaximum");
    }
  }
};
