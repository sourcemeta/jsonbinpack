namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules
class UnsatisfiableMaxContains final : public sourcemeta::alterschema::Rule {
public:
  UnsatisfiableMaxContains() : Rule("unsatisfiable_max_contains"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           sourcemeta::jsontoolkit::defines(schema, "maxContains") &&
           sourcemeta::jsontoolkit::is_integer(
               sourcemeta::jsontoolkit::at(schema, "maxContains")) &&
           sourcemeta::jsontoolkit::defines(schema, "maxItems") &&
           sourcemeta::jsontoolkit::is_integer(
               sourcemeta::jsontoolkit::at(schema, "maxItems")) &&
           sourcemeta::jsontoolkit::to_integer(
               sourcemeta::jsontoolkit::at(schema, "maxContains")) >=
               sourcemeta::jsontoolkit::to_integer(
                   sourcemeta::jsontoolkit::at(schema, "maxItems"));
  }

  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::erase(value, "maxContains");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
