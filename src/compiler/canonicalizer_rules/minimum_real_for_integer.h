class MinimumRealForInteger final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  MinimumRealForInteger() : SchemaTransformRule("minimum_real_for_integer"){};

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
           schema.defines("minimum") && schema.at("minimum").is_real();
  }

  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    const auto current{transformer.schema().at("minimum").to_real()};
    const auto new_value{static_cast<std::int64_t>(std::ceil(current))};
    transformer.assign("minimum", sourcemeta::jsontoolkit::JSON{new_value});
  }
};
