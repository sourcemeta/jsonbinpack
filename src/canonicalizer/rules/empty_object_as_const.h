namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_simplification
class EmptyObjectAsConst final : public sourcemeta::alterschema::Rule {
public:
  EmptyObjectAsConst() : Rule("empty_object_as_const"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &draft,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return draft == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           sourcemeta::jsontoolkit::defines(schema, "type") &&
           sourcemeta::jsontoolkit::is_string(
               sourcemeta::jsontoolkit::at(schema, "type")) &&
           sourcemeta::jsontoolkit::to_string(
               sourcemeta::jsontoolkit::at(schema, "type")) == "object" &&
           sourcemeta::jsontoolkit::defines(schema, "maxProperties") &&
           sourcemeta::jsontoolkit::is_integer(
               sourcemeta::jsontoolkit::at(schema, "maxProperties")) &&
           sourcemeta::jsontoolkit::to_integer(
               sourcemeta::jsontoolkit::at(schema, "maxProperties")) == 0;
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::assign(document, value, "const",
                                    sourcemeta::jsontoolkit::make_object());
    sourcemeta::jsontoolkit::erase(value, "maxProperties");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
