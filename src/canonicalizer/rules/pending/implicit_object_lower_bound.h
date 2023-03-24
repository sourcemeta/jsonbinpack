namespace sourcemeta::jsonbinpack::canonicalizer {

class ImplicitObjectLowerBound final : public sourcemeta::alterschema::Rule {
public:
  ImplicitObjectLowerBound() : Rule("implicit_object_lower_bound"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           schema.is_object() && schema.defines(keywords::validation::type) &&
           schema.at(keywords::validation::type) == "object" &&
           !schema.defines(keywords::validation::minProperties);
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    schema.assign(keywords::validation::minProperties,
                  static_cast<std::int64_t>(0));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
