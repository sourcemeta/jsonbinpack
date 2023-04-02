namespace sourcemeta::jsonbinpack::canonicalizer {

class DuplicateAnyOfBranches final : public sourcemeta::alterschema::Rule {
public:
  DuplicateAnyOfBranches() : Rule("duplicate_anyof_branches"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           sourcemeta::jsontoolkit::defines(schema, "anyOf") &&
           sourcemeta::jsontoolkit::is_array(
               sourcemeta::jsontoolkit::at(schema, "anyOf")) &&
           is_unique(sourcemeta::jsontoolkit::at(schema, "anyOf"));
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    auto &collection{sourcemeta::jsontoolkit::at(value, "anyOf")};
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
