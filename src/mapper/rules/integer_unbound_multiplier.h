namespace sourcemeta::jsonbinpack::mapper {

class IntegerUnboundMultiplier final : public sourcemeta::alterschema::Rule {
public:
  IntegerUnboundMultiplier() : Rule("integer_unbound_multiplier"){};

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
               sourcemeta::jsontoolkit::at(schema, "type")) == "integer" &&
           !sourcemeta::jsontoolkit::defines(schema, "minimum") &&
           !sourcemeta::jsontoolkit::defines(schema, "maximum") &&
           sourcemeta::jsontoolkit::defines(schema, "multipleOf") &&
           sourcemeta::jsontoolkit::is_integer(
               sourcemeta::jsontoolkit::at(schema, "multipleOf"));
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    const auto multiplier{sourcemeta::jsontoolkit::to_integer(
        sourcemeta::jsontoolkit::at(value, "multipleOf"))};
    auto options{sourcemeta::jsontoolkit::make_object()};
    sourcemeta::jsontoolkit::assign(options, "multiplier",
                                    sourcemeta::jsontoolkit::from(multiplier));
    make_encoding(document, value, "ARBITRARY_MULTIPLE_ZIGZAG_VARINT", options);
  }
};

} // namespace sourcemeta::jsonbinpack::mapper
