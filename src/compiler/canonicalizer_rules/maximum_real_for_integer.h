class MaximumRealForInteger final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  MaximumRealForInteger() : SchemaTransformRule("maximum_real_for_integer"){};

  [[nodiscard]] auto condition(const sourcemeta::jsontoolkit::JSON &schema,
                               const std::string &dialect,
                               const std::set<std::string> &vocabularies,
                               const sourcemeta::jsontoolkit::Pointer &) const
      -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.defines("type") &&
           schema.at("type").is_string() &&
           schema.at("type").to_string() == "integer" &&
           schema.defines("maximum") && schema.at("maximum").is_real();
  }

  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    const auto current{transformer.schema().at("maximum").to_real()};
    const auto new_value{static_cast<std::int64_t>(std::floor(current))};
    transformer.assign("maximum", sourcemeta::jsontoolkit::JSON{new_value});
  }
};
