class DuplicateEnumValues final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  DuplicateEnumValues() : SchemaTransformRule("duplicate_enum_values"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON &schema,
            const std::string &dialect,
            const std::set<std::string> &vocabularies,
            const sourcemeta::jsontoolkit::Pointer &) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           schema.is_object() && schema.defines("enum") &&
           schema.at("enum").is_array() && !is_unique(schema.at("enum"));
  }

  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    auto collection = transformer.schema().at("enum");
    std::sort(collection.as_array().begin(), collection.as_array().end());
    auto last =
        std::unique(collection.as_array().begin(), collection.as_array().end());
    collection.erase(last, collection.as_array().end());
    transformer.replace({"enum"}, std::move(collection));
  }
};
