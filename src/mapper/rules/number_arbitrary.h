namespace sourcemeta::jsonbinpack::mapper {

class NumberArbitrary final : public sourcemeta::alterschema::Rule {
public:
  NumberArbitrary() : Rule("number_arbitrary"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return !is_encoding(schema) &&
           dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::defines(schema, "type") &&
           sourcemeta::jsontoolkit::to_string(
               sourcemeta::jsontoolkit::at(schema, "type")) == "number";
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    make_encoding(document, value, "DOUBLE_VARINT_TUPLE",
                  sourcemeta::jsontoolkit::make_object());
  }
};

} // namespace sourcemeta::jsonbinpack::mapper
