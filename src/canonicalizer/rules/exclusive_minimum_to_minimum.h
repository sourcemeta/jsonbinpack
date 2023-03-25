namespace sourcemeta::jsonbinpack::canonicalizer {

class ExclusiveMinimumToMinimum final : public sourcemeta::alterschema::Rule {
public:
  ExclusiveMinimumToMinimum() : Rule("exclusive_minimum_to_minimum"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           sourcemeta::jsontoolkit::defines(schema, "exclusiveMinimum") &&
           sourcemeta::jsontoolkit::is_number(
               sourcemeta::jsontoolkit::at(schema, "exclusiveMinimum")) &&
           !sourcemeta::jsontoolkit::defines(schema, "minimum");
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    // TODO: Can we extract this logic into a common
    // sourcemeta::jsontoolkit::plus(document, int) function?
    const auto new_minimum{
        sourcemeta::jsontoolkit::is_real(
            sourcemeta::jsontoolkit::at(value, "exclusiveMinimum"))
            ? sourcemeta::jsontoolkit::from(
                  sourcemeta::jsontoolkit::to_real(
                      sourcemeta::jsontoolkit::at(value, "exclusiveMinimum")) +
                  1.0)
            : sourcemeta::jsontoolkit::from(
                  sourcemeta::jsontoolkit::to_integer(
                      sourcemeta::jsontoolkit::at(value, "exclusiveMinimum")) +
                  1)};

    sourcemeta::jsontoolkit::assign(document, value, "minimum", new_minimum);
    sourcemeta::jsontoolkit::erase(value, "exclusiveMinimum");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer