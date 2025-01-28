class IntegerBoundedMultiplierGreaterThan8Bit final
    : public sourcemeta::core::SchemaTransformRule {
public:
  IntegerBoundedMultiplierGreaterThan8Bit()
      : sourcemeta::core::SchemaTransformRule{
            "integer_bounded_multiplier_greater_than_8_bit", ""} {};

  [[nodiscard]] auto condition(const sourcemeta::core::JSON &schema,
                               const std::string &dialect,
                               const std::set<std::string> &vocabularies,
                               const sourcemeta::core::Pointer &) const
      -> bool override {
    if (dialect != "https://json-schema.org/draft/2020-12/schema" ||
        !vocabularies.contains(
            "https://json-schema.org/draft/2020-12/vocab/validation") ||
        !schema.defines("type") || schema.at("type").to_string() != "integer" ||
        !schema.defines("minimum") || !schema.at("minimum").is_integer() ||
        !schema.defines("maximum") || !schema.at("maximum").is_integer() ||
        !schema.defines("multipleOf") ||
        !schema.at("multipleOf").is_integer()) {
      return false;
    }

    return !is_byte(count_multiples(schema.at("minimum").to_integer(),
                                    schema.at("maximum").to_integer(),
                                    schema.at("multipleOf").to_integer()));
  }

  auto transform(sourcemeta::core::PointerProxy &transformer) const
      -> void override {
    auto minimum = transformer.value().at("minimum");
    auto multiplier = transformer.value().at("multipleOf");
    auto options = sourcemeta::core::JSON::make_object();
    options.assign("minimum", std::move(minimum));
    options.assign("multiplier", std::move(multiplier));
    make_encoding(transformer, "FLOOR_MULTIPLE_ENUM_VARINT", options);
  }
};
