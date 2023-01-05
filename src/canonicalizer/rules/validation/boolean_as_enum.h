namespace sourcemeta::jsonbinpack::canonicalizer {

class BooleanAsEnum final : public sourcemeta::alterschema::Rule {
public:
  BooleanAsEnum() : Rule("boolean_as_enum"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           sourcemeta::jsontoolkit::defines(schema, "type") &&
           sourcemeta::jsontoolkit::to_string(
               sourcemeta::jsontoolkit::at(schema, "type")) == "boolean" &&
           !sourcemeta::jsontoolkit::defines(schema, "enum");
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    auto choices{sourcemeta::jsontoolkit::make_array()};
    sourcemeta::jsontoolkit::push_back(choices,
                                       sourcemeta::jsontoolkit::from(false));
    sourcemeta::jsontoolkit::push_back(choices,
                                       sourcemeta::jsontoolkit::from(true));
    sourcemeta::jsontoolkit::assign(document, value, "enum", choices);
    sourcemeta::jsontoolkit::erase(value, "type");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
