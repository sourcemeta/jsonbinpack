namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules
class ExclusiveMinimumToMinimum final : public sourcemeta::alterschema::Rule {
public:
  ExclusiveMinimumToMinimum() : Rule("exclusive_minimum_to_minimum"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &draft,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return draft == "https://json-schema.org/draft/2020-12/schema" &&
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
    auto new_minimum{sourcemeta::jsontoolkit::from(
        sourcemeta::jsontoolkit::at(value, "exclusiveMinimum"))};
    sourcemeta::jsontoolkit::add(new_minimum, sourcemeta::jsontoolkit::from(1));
    sourcemeta::jsontoolkit::assign(document, value, "minimum", new_minimum);
    sourcemeta::jsontoolkit::erase(value, "exclusiveMinimum");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
