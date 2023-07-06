namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules
class ConstAsEnum final : public sourcemeta::alterschema::Rule {
public:
  ConstAsEnum() : Rule("const_as_enum"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &draft,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return draft == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           sourcemeta::jsontoolkit::defines(schema, "const");
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::JSON values{sourcemeta::jsontoolkit::make_array()};
    sourcemeta::jsontoolkit::push_back(
        values, sourcemeta::jsontoolkit::at(value, "const"));
    sourcemeta::jsontoolkit::assign(document, value, "enum", values);
    sourcemeta::jsontoolkit::erase(value, "const");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
