namespace sourcemeta::jsonbinpack::canonicalizer {

class EmptyObjectAsConst final : public sourcemeta::alterschema::Rule {
public:
  EmptyObjectAsConst() : Rule("empty_object_as_const"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           schema.is_object() && schema.defines(keywords::validation::type) &&
           schema.at(keywords::validation::type) == "object" &&
           schema.defines(keywords::validation::maxProperties) &&
           schema.at(keywords::validation::maxProperties).is_integer() &&
           schema.at(keywords::validation::maxProperties) == 0;
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    schema.assign(
        "const",
        std::map<std::string, sourcemeta::jsontoolkit::JSON<std::string>>{});
    schema.erase(keywords::validation::maxProperties);
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
