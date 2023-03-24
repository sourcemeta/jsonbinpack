namespace sourcemeta::jsonbinpack::canonicalizer {

class EmptyDependentRequired final : public sourcemeta::alterschema::Rule {
public:
  EmptyDependentRequired() : Rule("empty_dependent_required"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           schema.is_object() &&
           schema.defines(keywords::validation::dependentRequired) &&
           schema.at(keywords::validation::dependentRequired).empty();
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    schema.erase(keywords::validation::dependentRequired);
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
