namespace sourcemeta::jsonbinpack::mapper {

/// @ingroup mapper_rules
class EnumSingleton final : public sourcemeta::alterschema::Rule {
public:
  EnumSingleton() : Rule("enum_singleton"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return !is_encoding(schema) &&
           dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::defines(schema, "enum") &&
           sourcemeta::jsontoolkit::is_array(
               sourcemeta::jsontoolkit::at(schema, "enum")) &&
           sourcemeta::jsontoolkit::size(
               sourcemeta::jsontoolkit::at(schema, "enum")) == 1;
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    auto options{sourcemeta::jsontoolkit::make_object()};
    sourcemeta::jsontoolkit::assign(
        options, "value",
        sourcemeta::jsontoolkit::from(sourcemeta::jsontoolkit::front(
            sourcemeta::jsontoolkit::at(value, "enum"))));

    make_encoding(document, value, "CONST_NONE", options);
  }
};

} // namespace sourcemeta::jsonbinpack::mapper
