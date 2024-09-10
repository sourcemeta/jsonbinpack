class BooleanSchemaTrue final : public sourcemeta::alterschema::Rule {
public:
  BooleanSchemaTrue() : Rule("boolean_schema_true", "TODO") {};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON &schema, const std::string &,
            const std::set<std::string> &,
            const sourcemeta::jsontoolkit::Pointer &) const -> bool override {
    return schema.is_boolean() && schema.to_boolean();
  }

  auto transform(sourcemeta::alterschema::Transformer &transformer) const
      -> void override {
    transformer.replace(sourcemeta::jsontoolkit::JSON::make_object());
  }
};
