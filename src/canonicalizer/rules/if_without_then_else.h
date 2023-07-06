namespace sourcemeta::jsonbinpack::canonicalizer {

// Note that dropping `if`, even if the other related keywords
// are not used, results in potential dropped annotations.
// However, this is fine in the context of JSON BinPack,
// as it does not rely on these type of annotations.
/// @ingroup canonicalizer_rules
class IfWithoutThenElse final : public sourcemeta::alterschema::Rule {
public:
  IfWithoutThenElse() : Rule("if_without_then_else"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &draft,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return draft == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           sourcemeta::jsontoolkit::defines(schema, "if") &&
           !sourcemeta::jsontoolkit::defines(schema, "then") &&
           !sourcemeta::jsontoolkit::defines(schema, "else");
  }

  auto transform(sourcemeta::jsontoolkit::JSON &,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::erase(value, "if");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
