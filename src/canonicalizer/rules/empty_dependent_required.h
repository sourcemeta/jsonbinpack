namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_superfluous
class EmptyDependentRequired final : public sourcemeta::alterschema::Rule {
public:
  EmptyDependentRequired() : Rule("empty_dependent_required"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &draft,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return draft == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           sourcemeta::jsontoolkit::defines(schema, "dependentRequired") &&
           sourcemeta::jsontoolkit::is_object(
               sourcemeta::jsontoolkit::at(schema, "dependentRequired")) &&
           sourcemeta::jsontoolkit::empty(
               sourcemeta::jsontoolkit::at(schema, "dependentRequired"));
  }

  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::erase(value, "dependentRequired");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
