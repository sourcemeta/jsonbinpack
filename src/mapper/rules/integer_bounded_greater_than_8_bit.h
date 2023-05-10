namespace sourcemeta::jsonbinpack::mapper {

class IntegerBoundedGreaterThan8Bit final
    : public sourcemeta::alterschema::Rule {
public:
  IntegerBoundedGreaterThan8Bit()
      : Rule("integer_bounded_greater_than_8_bit"){};

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
           sourcemeta::jsontoolkit::defines(schema, "minimum") &&
           sourcemeta::jsontoolkit::defines(schema, "maximum") &&
           !is_byte(sourcemeta::jsontoolkit::to_integer(
                        sourcemeta::jsontoolkit::at(schema, "maximum")) -
                    sourcemeta::jsontoolkit::to_integer(
                        sourcemeta::jsontoolkit::at(schema, "minimum"))) &&
           !sourcemeta::jsontoolkit::defines(schema, "multipleOf");
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    const auto minimum{sourcemeta::jsontoolkit::to_integer(
        sourcemeta::jsontoolkit::at(value, "minimum"))};
    auto options{sourcemeta::jsontoolkit::make_object()};
    sourcemeta::jsontoolkit::assign(options, "minimum",
                                    sourcemeta::jsontoolkit::from(minimum));
    sourcemeta::jsontoolkit::assign(options, "multiplier",
                                    sourcemeta::jsontoolkit::from(1));
    make_encoding(document, value, "FLOOR_MULTIPLE_ENUM_VARINT", options);
  }
};

} // namespace sourcemeta::jsonbinpack::mapper
