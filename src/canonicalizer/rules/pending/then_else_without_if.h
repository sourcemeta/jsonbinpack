namespace sourcemeta::jsonbinpack::canonicalizer {

class ThenElseWithoutIf final : public sourcemeta::alterschema::Rule {
public:
  ThenElseWithoutIf() : Rule("then_else_without_if"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::applicator) &&
           schema.is_object() && schema.defines(keywords::applicator::then) &&
           schema.defines(keywords::applicator::_else) &&
           !schema.defines(keywords::applicator::_if);
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    schema.erase(keywords::applicator::then);
    schema.erase(keywords::applicator::_else);
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
