namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_superfluous
class ImpliedArrayUniqueItemsByEnum final
    : public sourcemeta::alterschema::Rule {
public:
  ImpliedArrayUniqueItemsByEnum()
      : Rule("implied_array_unique_items_by_enum"){};
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
           sourcemeta::jsontoolkit::defines(schema, "enum") &&
           sourcemeta::jsontoolkit::is_array(
               sourcemeta::jsontoolkit::at(schema, "enum")) &&
           std::all_of(sourcemeta::jsontoolkit::cbegin_array(
                           sourcemeta::jsontoolkit::at(schema, "enum")),
                       sourcemeta::jsontoolkit::cend_array(
                           sourcemeta::jsontoolkit::at(schema, "enum")),
                       [](const auto &element) {
                         return !sourcemeta::jsontoolkit::is_array(element) ||
                                sourcemeta::jsontoolkit::size(element) <= 1;
                       });
  }

  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::erase(value, "uniqueItems");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
