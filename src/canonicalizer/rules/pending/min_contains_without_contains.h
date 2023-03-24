namespace sourcemeta::jsonbinpack::canonicalizer {

class MinContainsWithoutContains final : public sourcemeta::alterschema::Rule {
public:
  MinContainsWithoutContains() : Rule("min_contains_without_contains"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           schema.is_object() &&
           schema.defines(keywords::validation::minContains) &&
           !schema.defines(keywords::applicator::contains);
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    schema.erase(keywords::validation::minContains);
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
