namespace sourcemeta::jsonbinpack::canonicalizer {

class EmptyPatternProperties final : public sourcemeta::alterschema::Rule {
public:
  EmptyPatternProperties() : Rule("empty_pattern_properties"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::applicator) &&
           schema.is_object() &&
           schema.defines(keywords::applicator::patternProperties) &&
           schema.at(keywords::applicator::patternProperties).empty();
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    schema.erase(keywords::applicator::patternProperties);
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
