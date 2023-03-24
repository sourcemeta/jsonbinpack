namespace sourcemeta::jsonbinpack::canonicalizer {

class EmptyStringAsConst final : public sourcemeta::alterschema::Rule {
public:
  EmptyStringAsConst() : Rule("empty_string_as_const"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           schema.is_object() && schema.defines(keywords::validation::type) &&
           schema.at(keywords::validation::type) == "string" &&
           schema.defines(keywords::validation::maxLength) &&
           schema.at(keywords::validation::maxLength).is_integer() &&
           schema.at(keywords::validation::maxLength) == 0;
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    schema.assign(keywords::validation::_const, std::string{});
    schema.erase(keywords::validation::maxLength);
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
