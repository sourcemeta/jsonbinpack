namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class ConstAsEnum final : public sourcemeta::alterschema::Rule {
public:
  ConstAsEnum() : Rule("const_as_enum"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    return vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           sourcemeta::jsontoolkit::defines(schema, "const");
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::assign(
        document, value, "enum",
        sourcemeta::jsontoolkit::from(
            sourcemeta::jsontoolkit::at(value, "const")));
    sourcemeta::jsontoolkit::erase(value, "const");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
