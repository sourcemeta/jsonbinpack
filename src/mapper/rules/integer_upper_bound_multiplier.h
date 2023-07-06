namespace sourcemeta::jsonbinpack::mapper {

/// @ingroup mapper_rules
class IntegerUpperBoundMultiplier final : public sourcemeta::alterschema::Rule {
public:
  IntegerUpperBoundMultiplier() : Rule("integer_upper_bound_multiplier"){};

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
           sourcemeta::jsontoolkit::defines(schema, "multipleOf") &&
           sourcemeta::jsontoolkit::is_integer(
               sourcemeta::jsontoolkit::at(schema, "multipleOf"));
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    const auto maximum{sourcemeta::jsontoolkit::to_integer(
        sourcemeta::jsontoolkit::at(value, "maximum"))};
    const auto multiplier{sourcemeta::jsontoolkit::to_integer(
        sourcemeta::jsontoolkit::at(value, "multipleOf"))};
    auto options{sourcemeta::jsontoolkit::make_object()};
    sourcemeta::jsontoolkit::assign(options, "maximum",
                                    sourcemeta::jsontoolkit::from(maximum));
    sourcemeta::jsontoolkit::assign(options, "multiplier",
                                    sourcemeta::jsontoolkit::from(multiplier));
    make_encoding(document, value, "ROOF_MULTIPLE_MIRROR_ENUM_VARINT", options);
  }
};

} // namespace sourcemeta::jsonbinpack::mapper
