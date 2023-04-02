namespace sourcemeta::jsonbinpack::canonicalizer {

class DuplicateAllOfBranches final : public sourcemeta::alterschema::Rule {
public:
  DuplicateAllOfBranches() : Rule("duplicate_allof_branches"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    if (dialect != "https://json-schema.org/draft/2020-12/schema" ||
        !vocabularies.contains(
            "https://json-schema.org/draft/2020-12/vocab/applicator") ||
        !sourcemeta::jsontoolkit::is_object(schema) ||
        !sourcemeta::jsontoolkit::defines(schema, "allOf") ||
        !sourcemeta::jsontoolkit::is_array(
            sourcemeta::jsontoolkit::at(schema, "allOf"))) {
      return false;
    }

    auto copy{sourcemeta::jsontoolkit::from(
        sourcemeta::jsontoolkit::at(schema, "allOf"))};
    std::sort(sourcemeta::jsontoolkit::begin_array(copy),
              sourcemeta::jsontoolkit::end_array(copy),
              sourcemeta::jsontoolkit::compare);
    return std::unique(sourcemeta::jsontoolkit::begin_array(copy),
                       sourcemeta::jsontoolkit::end_array(copy)) !=
           sourcemeta::jsontoolkit::end_array(copy);
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    auto &collection{sourcemeta::jsontoolkit::at(value, "allOf")};
    std::sort(sourcemeta::jsontoolkit::begin_array(collection),
              sourcemeta::jsontoolkit::end_array(collection),
              sourcemeta::jsontoolkit::compare);
    auto last = std::unique(sourcemeta::jsontoolkit::begin_array(collection),
                            sourcemeta::jsontoolkit::end_array(collection));
    sourcemeta::jsontoolkit::erase_many(
        collection, last, sourcemeta::jsontoolkit::end_array(collection));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
