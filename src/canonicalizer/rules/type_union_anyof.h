namespace sourcemeta::jsonbinpack::canonicalizer {

// TODO: Document this rule
/// @ingroup canonicalizer_rules_heterogeneous
class TypeUnionAnyOf final : public sourcemeta::alterschema::Rule {
public:
  TypeUnionAnyOf() : Rule("type_union_anyof"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &draft,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t) const -> bool override {
    return draft == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/validation") &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           sourcemeta::jsontoolkit::is_object(schema) &&
           sourcemeta::jsontoolkit::defines(schema, "type") &&
           sourcemeta::jsontoolkit::is_array(
               sourcemeta::jsontoolkit::at(schema, "type"));
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    sourcemeta::jsontoolkit::JSON disjunctors{
        sourcemeta::jsontoolkit::make_array()};
    for (const auto &type : sourcemeta::jsontoolkit::array_iterator(
             sourcemeta::jsontoolkit::at(value, "type"))) {
      auto copy{sourcemeta::jsontoolkit::from(value)};
      // TODO: Handle $id too and other top-level keywords that should not
      // remain
      sourcemeta::jsontoolkit::erase(copy, "$schema");
      sourcemeta::jsontoolkit::assign(copy, "type", type);
      sourcemeta::jsontoolkit::push_back(disjunctors, copy);
    }

    sourcemeta::jsontoolkit::clear_except(value, {"$schema"});
    sourcemeta::jsontoolkit::assign(document, value, "anyOf", disjunctors);
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
