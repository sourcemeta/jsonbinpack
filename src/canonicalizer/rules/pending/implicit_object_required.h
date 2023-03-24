namespace sourcemeta::jsonbinpack::canonicalizer {

class ImplicitObjectRequired final : public sourcemeta::alterschema::Rule {
public:
  ImplicitObjectRequired() : Rule("implicit_object_required"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           schema.is_object() && schema.defines(keywords::validation::type) &&
           schema.at(keywords::validation::type) == "object" &&
           !schema.defines(keywords::validation::required);
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    std::vector<sourcemeta::jsontoolkit::JSON<std::string>> required{};
    schema.assign(keywords::validation::required, std::move(required));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
