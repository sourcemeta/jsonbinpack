class BooleanSchema final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  BooleanSchema() : SchemaTransformRule("boolean_schema"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON &schema, const std::string &,
            const std::set<std::string> &,
            const sourcemeta::jsontoolkit::Pointer &) const -> bool override {
    return schema.is_boolean();
  }

  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    const bool current_value{transformer.schema().to_boolean()};
    transformer.replace(sourcemeta::jsontoolkit::JSON::make_object());
    if (!current_value) {
      transformer.assign("not", sourcemeta::jsontoolkit::JSON::make_object());
    }
  }
};
