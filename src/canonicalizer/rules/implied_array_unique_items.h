namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules
class ImpliedArrayUniqueItems final : public sourcemeta::alterschema::Rule {
public:
  ImpliedArrayUniqueItems() : Rule("implied_array_unique_items"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    const bool singular_by_max_items{
        dialect == "https://json-schema.org/draft/2020-12/schema" &&
        vocabularies.contains(
            "https://json-schema.org/draft/2020-12/vocab/validation") &&
        sourcemeta::jsontoolkit::is_object(schema) &&
        sourcemeta::jsontoolkit::defines(schema, "maxItems") &&
        sourcemeta::jsontoolkit::is_integer(
            sourcemeta::jsontoolkit::at(schema, "maxItems")) &&
        sourcemeta::jsontoolkit::to_integer(
            sourcemeta::jsontoolkit::at(schema, "maxItems")) <= 1};

    const bool singular_by_const{
        dialect == "https://json-schema.org/draft/2020-12/schema" &&
        vocabularies.contains(
            "https://json-schema.org/draft/2020-12/vocab/validation") &&
        sourcemeta::jsontoolkit::is_object(schema) &&
        sourcemeta::jsontoolkit::defines(schema, "const") &&
        sourcemeta::jsontoolkit::is_array(
            sourcemeta::jsontoolkit::at(schema, "const")) &&
        sourcemeta::jsontoolkit::size(
            sourcemeta::jsontoolkit::at(schema, "const")) <= 1};

    const bool singular_by_enum{
        dialect == "https://json-schema.org/draft/2020-12/schema" &&
        vocabularies.contains(
            "https://json-schema.org/draft/2020-12/vocab/validation") &&
        sourcemeta::jsontoolkit::is_object(schema) &&
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
                    })};

    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           sourcemeta::jsontoolkit::defines(schema, "uniqueItems") &&
           sourcemeta::jsontoolkit::is_boolean(
               sourcemeta::jsontoolkit::at(schema, "uniqueItems")) &&
           sourcemeta::jsontoolkit::to_boolean(
               sourcemeta::jsontoolkit::at(schema, "uniqueItems")) &&
           (singular_by_max_items || singular_by_const || singular_by_enum);
  }

  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::erase(value, "uniqueItems");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
