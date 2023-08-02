namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_syntax_sugar
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// According to the JSON grammar, boolean values consist of two constants:
/// `false` and `true`. As such, setting the `type` JSON Schema keyword
/// from the Validation vocabulary to `boolean` is equivalent to explicitly
/// declaring the `enum` keyword from the Validation vocabulary to the
/// constants `false` and `true`.
///
/// \f[\frac{s.type = boolean}{s \mapsto s \cup \{ enum \mapsto \langle false,
/// true \rangle \} \setminus \{ type \} }\f]

class BooleanAsEnum final : public sourcemeta::alterschema::Rule {
public:
  BooleanAsEnum() : Rule("boolean_as_enum"){};

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
               sourcemeta::jsontoolkit::at(schema, "type")) == "boolean" &&
           !sourcemeta::jsontoolkit::defines(schema, "enum");
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    auto choices{sourcemeta::jsontoolkit::make_array()};
    sourcemeta::jsontoolkit::push_back(choices,
                                       sourcemeta::jsontoolkit::from(false));
    sourcemeta::jsontoolkit::push_back(choices,
                                       sourcemeta::jsontoolkit::from(true));
    sourcemeta::jsontoolkit::assign(document, value, "enum", choices);
    sourcemeta::jsontoolkit::erase(value, "type");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
