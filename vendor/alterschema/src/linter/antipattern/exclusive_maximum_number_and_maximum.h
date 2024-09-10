class ExclusiveMaximumNumberAndMaximum final : public Rule {
public:
  ExclusiveMaximumNumberAndMaximum()
      : Rule{"exclusive_maximum_number_and_maximum",
             "Setting both `exclusiveMaximum` and `maximum` at the same time "
             "is considered an anti-pattern. You should choose one"} {};

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
           schema.is_object() && schema.defines("maximum") &&
           schema.defines("exclusiveMaximum") &&
           schema.at("maximum").is_number() &&
           schema.at("exclusiveMaximum").is_number();
  }

  auto transform(Transformer &transformer) const -> void override {
    if (transformer.schema().at("maximum") <
        transformer.schema().at("exclusiveMaximum")) {
      transformer.erase("exclusiveMaximum");
    } else {
      transformer.erase("maximum");
    }
  }
};
