namespace sourcemeta::jsonbinpack::canonicalizer {

class UnsatisfiableMaxContains final : public sourcemeta::alterschema::Rule {
public:
  UnsatisfiableMaxContains() : Rule("unsatisfiable_max_contains"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           schema.is_object() &&
           schema.defines(keywords::validation::maxContains) &&
           schema.at(keywords::validation::maxContains).is_integer() &&
           schema.defines(keywords::validation::maxItems) &&
           schema.at(keywords::validation::maxItems).is_integer() &&
           schema.at(keywords::validation::maxContains).to_integer() >=
               schema.at(keywords::validation::maxItems).to_integer();
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    schema.erase(keywords::validation::maxContains);
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
