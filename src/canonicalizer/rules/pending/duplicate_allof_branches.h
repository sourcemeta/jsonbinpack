namespace sourcemeta::jsonbinpack::canonicalizer {

class DuplicateAllOfBranches final : public sourcemeta::alterschema::Rule {
public:
  DuplicateAllOfBranches() : Rule("duplicate_allof_branches"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    if (!sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
            schema, vocabularies::applicator) ||
        !schema.is_object() || !schema.defines(keywords::applicator::allOf) ||
        !schema.at(keywords::applicator::allOf).is_array()) {
      return false;
    }

    auto copy{schema.at(keywords::applicator::allOf).to_array()};
    std::sort(std::begin(copy), std::end(copy));
    return std::unique(std::begin(copy), std::end(copy)) != std::end(copy);
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    auto &array = schema.at(keywords::applicator::allOf).to_array();
    std::sort(std::begin(array), std::end(array));
    auto last = std::unique(std::begin(array), std::end(array));
    schema.at(keywords::applicator::allOf).erase(last, std::end(array));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer