namespace sourcemeta::jsonbinpack::canonicalizer {

class ImplicitTypeUnion final : public sourcemeta::alterschema::Rule {
public:
  ImplicitTypeUnion() : Rule("implicit_type_union"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    // TODO: Write rules that flatten allOf/oneOf/anyOf with one element
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           (!vocabularies.contains(
                "https://json-schema.org/draft/2020-12/vocab/core") ||
            !sourcemeta::jsontoolkit::defines_any(schema,
                                                  {"$ref", "$dynamicRef"})) &&
           (!vocabularies.contains(
                "https://json-schema.org/draft/2020-12/vocab/applicator") ||
            !sourcemeta::jsontoolkit::defines_any(
                schema,
                {"anyOf", "allOf", "oneOf", "not", "if", "then", "else"})) &&
           (!vocabularies.contains(
                "https://json-schema.org/draft/2020-12/vocab/validation") ||
            !sourcemeta::jsontoolkit::defines_any(schema,
                                                  {"type", "const", "enum"}));
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
