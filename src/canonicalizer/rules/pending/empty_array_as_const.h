namespace sourcemeta::jsonbinpack::canonicalizer {

class EmptyArrayAsConst final : public sourcemeta::alterschema::Rule {
public:
  EmptyArrayAsConst() : Rule("empty_array_as_const"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           schema.is_object() && schema.defines(keywords::validation::type) &&
           schema.at(keywords::validation::type) == "array" &&
           schema.defines(keywords::validation::maxItems) &&
           schema.at(keywords::validation::maxItems).is_integer() &&
           schema.at(keywords::validation::maxItems) == 0;
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    schema.assign(keywords::validation::_const,
                  std::vector<sourcemeta::jsontoolkit::JSON<std::string>>{});
    schema.erase(keywords::validation::maxItems);
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
