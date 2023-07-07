namespace sourcemeta::jsonbinpack::mapper {

/// @ingroup mapper_rules
class IntegerUpperBound final : public sourcemeta::alterschema::Rule {
public:
  IntegerUpperBound() : Rule("integer_upper_bound"){};

  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &draft,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return !is_encoding(schema) &&
           draft == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::defines(schema, "type") &&
           sourcemeta::jsontoolkit::to_string(
               sourcemeta::jsontoolkit::at(schema, "type")) == "integer" &&
           !sourcemeta::jsontoolkit::defines(schema, "minimum") &&
           sourcemeta::jsontoolkit::defines(schema, "maximum") &&
           !sourcemeta::jsontoolkit::defines(schema, "multipleOf");
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    const auto maximum{sourcemeta::jsontoolkit::to_integer(
        sourcemeta::jsontoolkit::at(value, "maximum"))};
    auto options{sourcemeta::jsontoolkit::make_object()};
    sourcemeta::jsontoolkit::assign(options, "maximum",
                                    sourcemeta::jsontoolkit::from(maximum));
    sourcemeta::jsontoolkit::assign(options, "multiplier",
                                    sourcemeta::jsontoolkit::from(1));
    make_encoding(document, value, "ROOF_MULTIPLE_MIRROR_ENUM_VARINT", options);
  }
};

} // namespace sourcemeta::jsonbinpack::mapper
