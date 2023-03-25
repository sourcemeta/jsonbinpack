namespace sourcemeta::jsonbinpack::canonicalizer {

class ExclusiveMaximumAndMaximum final : public sourcemeta::alterschema::Rule {
public:
  ExclusiveMaximumAndMaximum() : Rule("exclusive_maximum_and_maximum"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           sourcemeta::jsontoolkit::defines(schema, "maximum") &&
           sourcemeta::jsontoolkit::defines(schema, "exclusiveMaximum") &&
           sourcemeta::jsontoolkit::is_number(
               sourcemeta::jsontoolkit::at(schema, "maximum")) &&
           sourcemeta::jsontoolkit::is_number(
               sourcemeta::jsontoolkit::at(schema, "exclusiveMaximum"));
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    const bool maximum_less_than_exclusive_maximum{
        compare_number(sourcemeta::jsontoolkit::at(value, "maximum"),
                       sourcemeta::jsontoolkit::at(value, "exclusiveMaximum"))};
    if (maximum_less_than_exclusive_maximum) {
      sourcemeta::jsontoolkit::erase(value, "exclusiveMaximum");
    } else {
      sourcemeta::jsontoolkit::erase(value, "maximum");
    }
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
