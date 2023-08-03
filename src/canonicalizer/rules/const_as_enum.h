namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_syntax_sugar
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/validation | Y        |
///
/// The JSON Schema Validation vocabulary defines the `enum` keyword to
/// declare a set of matching values and the `const` keyword to define
/// a single matching value. As such, `const` is an enumeration consisting
/// of a single value.
///
/// \f[\frac{const \in dom(S)}{S \mapsto S \cup \{ enum \mapsto \langle S.const
/// \rangle \} \setminus \{const\} }\f]

class ConstAsEnum final : public sourcemeta::alterschema::Rule {
public:
  ConstAsEnum() : Rule("const_as_enum"){};

  /// The rule condition
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &draft,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return draft == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           sourcemeta::jsontoolkit::defines(schema, "const");
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::JSON values{sourcemeta::jsontoolkit::make_array()};
    sourcemeta::jsontoolkit::push_back(
        values, sourcemeta::jsontoolkit::at(value, "const"));
    sourcemeta::jsontoolkit::assign(document, value, "enum", values);
    sourcemeta::jsontoolkit::erase(value, "const");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
