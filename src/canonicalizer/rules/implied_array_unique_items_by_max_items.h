namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_superfluous
class ImpliedArrayUniqueItemsByMaxItems final
    : public sourcemeta::alterschema::Rule {
public:
  ImpliedArrayUniqueItemsByMaxItems()
      : Rule("implied_array_unique_items_by_max_items"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &draft,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return draft == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           sourcemeta::jsontoolkit::defines(schema, "uniqueItems") &&
           sourcemeta::jsontoolkit::is_boolean(
               sourcemeta::jsontoolkit::at(schema, "uniqueItems")) &&
           sourcemeta::jsontoolkit::to_boolean(
               sourcemeta::jsontoolkit::at(schema, "uniqueItems")) &&
           sourcemeta::jsontoolkit::defines(schema, "maxItems") &&
           sourcemeta::jsontoolkit::is_integer(
               sourcemeta::jsontoolkit::at(schema, "maxItems")) &&
           sourcemeta::jsontoolkit::to_integer(
               sourcemeta::jsontoolkit::at(schema, "maxItems")) <= 1;
  }

  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::erase(value, "uniqueItems");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
