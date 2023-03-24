namespace sourcemeta::jsonbinpack::canonicalizer {

class ImplicitUnitMultipleOf final : public sourcemeta::alterschema::Rule {
public:
  ImplicitUnitMultipleOf() : Rule("implicit_unit_multiple_of"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           schema.is_object() && schema.defines(keywords::validation::type) &&
           schema.at(keywords::validation::type) == "integer" &&
           !schema.defines(keywords::validation::multipleOf);
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    schema.assign(keywords::validation::multipleOf,
                  static_cast<std::int64_t>(1));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
