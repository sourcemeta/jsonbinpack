class IntegerBoundedMultiplier8Bit final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  IntegerBoundedMultiplier8Bit()
      : sourcemeta::jsontoolkit::SchemaTransformRule(
            "integer_bounded_multiplier_8_bit"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON &schema,
            const std::string &dialect,
            const std::set<std::string> &vocabularies,
            const sourcemeta::jsontoolkit::Pointer &) const -> bool override {
    if (is_encoding(schema) ||
        dialect != "https://json-schema.org/draft/2020-12/schema" ||
        !vocabularies.contains(
            "https://json-schema.org/draft/2020-12/vocab/validation") ||
        !schema.defines("type") || schema.at("type").to_string() != "integer" ||
        !schema.defines("minimum") || !schema.defines("maximum") ||
        !schema.defines("multipleOf") ||
        !schema.at("multipleOf").is_integer()) {
      return false;
    }

    const std::optional<std::vector<sourcemeta::jsontoolkit::JSON>> states{
        states_integer(schema, vocabularies)};
    return states.has_value() &&
           states->size() <= std::numeric_limits<std::uint8_t>::max();
  }

  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    auto minimum = transformer.schema().at("minimum");
    auto maximum = transformer.schema().at("maximum");
    auto multiplier = transformer.schema().at("multipleOf");

    auto options = sourcemeta::jsontoolkit::JSON::make_object();
    options.assign("minimum", std::move(minimum));
    options.assign("maximum", std::move(maximum));
    options.assign("multiplier", std::move(multiplier));
    make_encoding(transformer, "BOUNDED_MULTIPLE_8BITS_ENUM_FIXED", options);
  }
};
