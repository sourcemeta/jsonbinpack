namespace sourcemeta::jsonbinpack::canonicalizer {

class NullAsConst final : public sourcemeta::alterschema::Rule {
public:
  NullAsConst() : Rule("null_as_const"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           schema.is_object() && schema.defines(keywords::validation::type) &&
           schema.at(keywords::validation::type) == "null";
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    schema.assign(keywords::validation::_const,
                  sourcemeta::jsontoolkit::JSON<std::string>{nullptr});
    schema.erase(keywords::validation::type);
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
