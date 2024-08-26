class MinPropertiesRequiredTautology final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  MinPropertiesRequiredTautology()
      : SchemaTransformRule("min_properties_required_tautology") {};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON &schema,
            const std::string &dialect,
            const std::set<std::string> &vocabularies,
            const sourcemeta::jsontoolkit::Pointer &) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.defines("minProperties") &&
           schema.at("minProperties").is_integer() &&
           schema.defines("required") && schema.at("required").is_array() &&
           is_unique(schema.at("required")) &&
           schema.at("required").size() >
               static_cast<std::uint64_t>(
                   schema.at("minProperties").to_integer());
  }

  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.assign("minProperties",
                       sourcemeta::jsontoolkit::JSON{
                           transformer.schema().at("required").size()});
  }
};
