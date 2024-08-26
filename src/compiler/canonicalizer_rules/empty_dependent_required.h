class EmptyDependentRequired final : public sourcemeta::alterschema::Rule {
public:
  EmptyDependentRequired() : Rule("empty_dependent_required") {};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON &schema,
            const std::string &dialect,
            const std::set<std::string> &vocabularies,
            const sourcemeta::jsontoolkit::Pointer &) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           schema.is_object() && schema.defines("dependentRequired") &&
           schema.at("dependentRequired").is_object() &&
           schema.at("dependentRequired").empty();
  }

  auto transform(sourcemeta::alterschema::Transformer &transformer) const
      -> void override {
    transformer.erase("dependentRequired");
  }
};
