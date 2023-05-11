namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules
class ExclusiveMinimumAndMinimum final : public sourcemeta::alterschema::Rule {
public:
  ExclusiveMinimumAndMinimum() : Rule("exclusive_minimum_and_minimum"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           sourcemeta::jsontoolkit::defines(schema, "minimum") &&
           sourcemeta::jsontoolkit::defines(schema, "exclusiveMinimum") &&
           sourcemeta::jsontoolkit::is_number(
               sourcemeta::jsontoolkit::at(schema, "minimum")) &&
           sourcemeta::jsontoolkit::is_number(
               sourcemeta::jsontoolkit::at(schema, "exclusiveMinimum"));
  }

  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    const bool exclusive_minimum_less_than_minimum{
        sourcemeta::jsontoolkit::compare(
            sourcemeta::jsontoolkit::at(value, "exclusiveMinimum"),
            sourcemeta::jsontoolkit::at(value, "minimum"))};
    if (exclusive_minimum_less_than_minimum) {
      sourcemeta::jsontoolkit::erase(value, "exclusiveMinimum");
    } else {
      sourcemeta::jsontoolkit::erase(value, "minimum");
    }
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
