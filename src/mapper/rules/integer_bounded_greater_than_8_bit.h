namespace sourcemeta::jsonbinpack::mapper {

/// @ingroup mapper_rules
class IntegerBoundedGreaterThan8Bit final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  IntegerBoundedGreaterThan8Bit()
      : sourcemeta::jsontoolkit::SchemaTransformRule(
            "integer_bounded_greater_than_8_bit"){};

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
           schema.defines("minimum") && schema.defines("maximum") &&
           !is_byte(schema.at("maximum").to_integer() -
                    schema.at("minimum").to_integer()) &&
           !schema.defines("multipleOf");
  }

  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    auto minimum{transformer.schema().at("minimum")};
    auto options = sourcemeta::jsontoolkit::JSON::make_object();
    options.assign("minimum", std::move(minimum));
    options.assign("multiplier", sourcemeta::jsontoolkit::JSON{1});
    make_encoding(transformer, "FLOOR_MULTIPLE_ENUM_VARINT", options);
  }
};

} // namespace sourcemeta::jsonbinpack::mapper
