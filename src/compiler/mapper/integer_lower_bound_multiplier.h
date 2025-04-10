class IntegerLowerBoundMultiplier final
    : public sourcemeta::core::SchemaTransformRule {
public:
  IntegerLowerBoundMultiplier()
      : sourcemeta::core::SchemaTransformRule{"integer_lower_bound_multiplier",
                                              ""} {};

  [[nodiscard]] auto condition(const sourcemeta::core::JSON &schema,
                               const std::string &dialect,
                               const std::set<std::string> &vocabularies,
                               const sourcemeta::core::Pointer &) const
      -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.defines("type") &&
           schema.at("type").to_string() == "integer" &&
           schema.defines("minimum") && !schema.defines("maximum") &&
           schema.defines("multipleOf") && schema.at("multipleOf").is_integer();
  }

  auto transform(sourcemeta::core::JSON &schema) const -> void override {
    auto minimum = schema.at("minimum");
    auto multiplier = schema.at("multipleOf");
    auto options = sourcemeta::core::JSON::make_object();
    options.assign("minimum", std::move(minimum));
    options.assign("multiplier", std::move(multiplier));
    make_encoding(schema, "FLOOR_MULTIPLE_ENUM_VARINT", options);
  }
};
