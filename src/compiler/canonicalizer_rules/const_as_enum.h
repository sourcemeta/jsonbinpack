class ConstAsEnum final : public sourcemeta::alterschema::Rule {
public:
  ConstAsEnum() : Rule("const_as_enum") {};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON &schema,
            const std::string &dialect,
            const std::set<std::string> &vocabularies,
            const sourcemeta::jsontoolkit::Pointer &) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.defines("const");
  }

  auto transform(sourcemeta::alterschema::Transformer &transformer) const
      -> void override {
    sourcemeta::jsontoolkit::JSON values =
        sourcemeta::jsontoolkit::JSON::make_array();
    values.push_back(transformer.schema().at("const"));
    transformer.assign("enum", values);
    transformer.erase("const");
  }
};
