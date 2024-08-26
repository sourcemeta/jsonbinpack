class ExclusiveMaximumAndMaximum final : public sourcemeta::alterschema::Rule {
public:
  ExclusiveMaximumAndMaximum() : Rule("exclusive_maximum_and_maximum") {};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON &schema,
            const std::string &dialect,
            const std::set<std::string> &vocabularies,
            const sourcemeta::jsontoolkit::Pointer &) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.defines("maximum") &&
           schema.defines("exclusiveMaximum") &&
           schema.at("maximum").is_number() &&
           schema.at("exclusiveMaximum").is_number();
  }

  auto transform(sourcemeta::alterschema::Transformer &transformer) const
      -> void override {
    if (transformer.schema().at("maximum") <
        transformer.schema().at("exclusiveMaximum")) {
      transformer.erase("exclusiveMaximum");
    } else {
      transformer.erase("maximum");
    }
  }
};
