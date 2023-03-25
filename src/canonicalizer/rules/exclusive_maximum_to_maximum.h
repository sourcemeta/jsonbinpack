namespace sourcemeta::jsonbinpack::canonicalizer {

class ExclusiveMaximumToMaximum final : public sourcemeta::alterschema::Rule {
public:
  ExclusiveMaximumToMaximum() : Rule("exclusive_maximum_to_maximum"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           sourcemeta::jsontoolkit::defines(schema, "exclusiveMaximum") &&
           sourcemeta::jsontoolkit::is_number(
               sourcemeta::jsontoolkit::at(schema, "exclusiveMaximum")) &&
           !sourcemeta::jsontoolkit::defines(schema, "maximum");
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    // TODO: Can we extract this logic into a common
    // sourcemeta::jsontoolkit::minus(document, int) function?
    const auto new_maximum{
        sourcemeta::jsontoolkit::is_real(
            sourcemeta::jsontoolkit::at(value, "exclusiveMaximum"))
            ? sourcemeta::jsontoolkit::from(
                  sourcemeta::jsontoolkit::to_real(
                      sourcemeta::jsontoolkit::at(value, "exclusiveMaximum")) -
                  1.0)
            : sourcemeta::jsontoolkit::from(
                  sourcemeta::jsontoolkit::to_integer(
                      sourcemeta::jsontoolkit::at(value, "exclusiveMaximum")) -
                  1)};

    sourcemeta::jsontoolkit::assign(document, value, "maximum", new_maximum);
    sourcemeta::jsontoolkit::erase(value, "exclusiveMaximum");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
