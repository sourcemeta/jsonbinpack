namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_heterogeneous
class ImplicitTypeUnion final : public sourcemeta::alterschema::Rule {
public:
  ImplicitTypeUnion() : Rule("implicit_type_union"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &draft,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    const bool has_core_blacklist{
        vocabularies.contains(
            "https://json-schema.org/draft/2020-12/vocab/core") &&
        sourcemeta::jsontoolkit::defines_any(schema, {"$ref", "$dynamicRef"})};
    const bool has_applicator_blacklist{
        vocabularies.contains(
            "https://json-schema.org/draft/2020-12/vocab/applicator") &&
        sourcemeta::jsontoolkit::defines_any(
            schema, {"anyOf", "allOf", "oneOf", "not", "if", "then", "else"})};
    const bool has_validation_blacklist{
        vocabularies.contains(
            "https://json-schema.org/draft/2020-12/vocab/validation") &&
        sourcemeta::jsontoolkit::defines_any(schema,
                                             {"type", "const", "enum"})};

    return draft == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::is_object(schema) && !has_core_blacklist &&
           !has_applicator_blacklist && !has_validation_blacklist;
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::JSON types{sourcemeta::jsontoolkit::make_array()};

    // All possible JSON Schema types
    // See
    // https://json-schema.org/draft/2020-12/json-schema-validation.html#rfc.section.6.1.1
    sourcemeta::jsontoolkit::push_back(types,
                                       sourcemeta::jsontoolkit::from("null"));
    sourcemeta::jsontoolkit::push_back(
        types, sourcemeta::jsontoolkit::from("boolean"));
    sourcemeta::jsontoolkit::push_back(types,
                                       sourcemeta::jsontoolkit::from("object"));
    sourcemeta::jsontoolkit::push_back(types,
                                       sourcemeta::jsontoolkit::from("array"));
    sourcemeta::jsontoolkit::push_back(types,
                                       sourcemeta::jsontoolkit::from("string"));
    sourcemeta::jsontoolkit::push_back(types,
                                       sourcemeta::jsontoolkit::from("number"));
    sourcemeta::jsontoolkit::push_back(
        types, sourcemeta::jsontoolkit::from("integer"));

    sourcemeta::jsontoolkit::assign(document, value, "type", types);
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
