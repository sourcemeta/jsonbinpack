namespace sourcemeta::jsonbinpack::mapper {

// TODO: Unit test this mapping once we have container encodings
class EnumArbitrary final : public sourcemeta::alterschema::Rule {
public:
  EnumArbitrary() : Rule("enum_arbitrary"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t level) const -> bool override {
    return !is_encoding(schema) &&
           dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::defines(schema, "enum") &&
           sourcemeta::jsontoolkit::is_array(
               sourcemeta::jsontoolkit::at(schema, "enum")) &&
           level > 0 &&
           sourcemeta::jsontoolkit::size(
               sourcemeta::jsontoolkit::at(schema, "enum")) > 1 &&
           !is_byte(sourcemeta::jsontoolkit::size(
                        sourcemeta::jsontoolkit::at(schema, "enum")) -
                    1);
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    auto options{sourcemeta::jsontoolkit::make_object()};
    sourcemeta::jsontoolkit::assign(
        options, "choices",
        sourcemeta::jsontoolkit::from(
            sourcemeta::jsontoolkit::at(value, "enum")));
    make_encoding(document, value, "LARGE_CHOICE_INDEX", options);
  }
};

} // namespace sourcemeta::jsonbinpack::mapper