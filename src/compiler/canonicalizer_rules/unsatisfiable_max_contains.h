class UnsatisfiableMaxContains final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  UnsatisfiableMaxContains()
      : SchemaTransformRule("unsatisfiable_max_contains"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON &schema,
            const std::string &dialect,
            const std::set<std::string> &vocabularies,
            const sourcemeta::jsontoolkit::Pointer &) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.defines("maxContains") &&
           schema.at("maxContains").is_integer() &&
           schema.defines("maxItems") && schema.at("maxItems").is_integer() &&
           schema.at("maxContains").to_integer() >=
               schema.at("maxItems").to_integer();
  }

  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    transformer.erase("maxContains");
  }
};
