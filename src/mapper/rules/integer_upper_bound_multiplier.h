namespace sourcemeta::jsonbinpack::mapper {

/// @ingroup mapper_rules
class IntegerUpperBoundMultiplier final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  IntegerUpperBoundMultiplier()
      : sourcemeta::jsontoolkit::SchemaTransformRule(
            "integer_upper_bound_multiplier"){};

  [[nodiscard]] auto condition(const sourcemeta::jsontoolkit::JSON &schema,
                               const std::string &dialect,
                               const std::set<std::string> &vocabularies,
                               const sourcemeta::jsontoolkit::Pointer &) const
      -> bool override {
    return !is_encoding(schema) &&
           dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.defines("type") &&
           schema.at("type").to_string() == "integer" &&
           !schema.defines("minimum") && schema.defines("maximum") &&
           schema.defines("multipleOf") && schema.at("multipleOf").is_integer();
  }

  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    auto maximum = transformer.schema().at("maximum");
    auto multiplier = transformer.schema().at("multipleOf");
    auto options = sourcemeta::jsontoolkit::JSON::make_object();
    options.assign("maximum", std::move(maximum));
    options.assign("multiplier", std::move(multiplier));
    make_encoding(transformer, "ROOF_MULTIPLE_MIRROR_ENUM_VARINT", options);
  }
};

} // namespace sourcemeta::jsonbinpack::mapper
