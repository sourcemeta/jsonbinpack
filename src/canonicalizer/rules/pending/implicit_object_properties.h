namespace sourcemeta::jsonbinpack::canonicalizer {

class ImplicitObjectProperties final : public sourcemeta::alterschema::Rule {
public:
  ImplicitObjectProperties() : Rule("implicit_object_properties"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::applicator) &&
           schema.is_object() && schema.defines(keywords::validation::type) &&
           schema.at(keywords::validation::type) == "object" &&
           !schema.defines(keywords::applicator::properties);
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    std::map<std::string, sourcemeta::jsontoolkit::JSON<std::string>>
        properties{};
    schema.assign(keywords::applicator::properties, std::move(properties));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
