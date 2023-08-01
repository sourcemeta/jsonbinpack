namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_simplification
class MaximumRealForInteger final : public sourcemeta::alterschema::Rule {
public:
  MaximumRealForInteger() : Rule("maximum_real_for_integer"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &draft,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return draft == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           sourcemeta::jsontoolkit::defines(schema, "type") &&
           sourcemeta::jsontoolkit::is_string(
               sourcemeta::jsontoolkit::at(schema, "type")) &&
           sourcemeta::jsontoolkit::to_string(
               sourcemeta::jsontoolkit::at(schema, "type")) == "integer" &&
           sourcemeta::jsontoolkit::defines(schema, "maximum") &&
           sourcemeta::jsontoolkit::is_real(
               sourcemeta::jsontoolkit::at(schema, "maximum"));
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    const auto current{sourcemeta::jsontoolkit::to_real(
        sourcemeta::jsontoolkit::at(value, "maximum"))};
    const auto new_value{static_cast<std::int64_t>(std::floor(current))};
    sourcemeta::jsontoolkit::assign(document, value, "maximum",
                                    sourcemeta::jsontoolkit::from(new_value));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
