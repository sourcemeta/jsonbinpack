class DuplicateAnyOfBranches final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  DuplicateAnyOfBranches() : SchemaTransformRule("duplicate_anyof_branches"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON &schema,
            const std::string &dialect,
            const std::set<std::string> &vocabularies,
            const sourcemeta::jsontoolkit::Pointer &) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           schema.is_object() && schema.defines("anyOf") &&
           schema.at("anyOf").is_array() && !is_unique(schema.at("anyOf"));
  }

  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    auto collection = transformer.schema().at("anyOf");
    std::sort(collection.as_array().begin(), collection.as_array().end());
    auto last =
        std::unique(collection.as_array().begin(), collection.as_array().end());
    collection.erase(last, collection.as_array().end());
    transformer.replace({"anyOf"}, std::move(collection));
  }
};
