namespace sourcemeta::jsonbinpack::canonicalizer {

class MinPropertiesRequiredTautology final
    : public sourcemeta::alterschema::Rule {
public:
  MinPropertiesRequiredTautology()
      : Rule("min_properties_required_tautology"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           schema.is_object() &&
           schema.defines(keywords::validation::minProperties) &&
           schema.at(keywords::validation::minProperties).is_integer() &&
           schema.defines(keywords::validation::required) &&
           schema.at(keywords::validation::required).is_array() &&
           static_cast<std::int64_t>(
               schema.at(keywords::validation::required).size()) >
               schema.at(keywords::validation::minProperties).to_integer();
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    schema.assign(keywords::validation::minProperties,
                  static_cast<std::int64_t>(
                      schema.at(keywords::validation::required).size()));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
