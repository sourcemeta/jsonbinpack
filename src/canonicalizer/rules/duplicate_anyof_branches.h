namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_simplification
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/applicator | Y        |
///
/// The `anyOf` keyword from the Applicator vocabulary represents a logical
/// disjunction. As such, duplicate branches do not affect the result and can be
/// removed.
///
/// \f[\frac{anyOf \in dom(S) \land \#S.anyOf \neq \#\{ x \mid S.anyOf \}}{S
/// \mapsto S \cup \{ anyOf \mapsto seq \; \{ x \mid S.anyOf \} \} }\f]

class DuplicateAnyOfBranches final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  DuplicateAnyOfBranches() : SchemaTransformRule("duplicate_anyof_branches"){};

  /// The rule condition
  [[nodiscard]] auto condition(const sourcemeta::jsontoolkit::JSON &schema,
                               const std::string &dialect,
                               const std::set<std::string> &vocabularies,
                               const sourcemeta::jsontoolkit::Pointer &) const
      -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           schema.is_object() && schema.defines("anyOf") &&
           schema.at("anyOf").is_array() && !is_unique(schema.at("anyOf"));
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    auto collection = transformer.schema().at("anyOf");
    std::sort(collection.as_array().begin(), collection.as_array().end());
    auto last =
        std::unique(collection.as_array().begin(), collection.as_array().end());
    collection.erase(last, collection.as_array().end());
    transformer.replace({"anyOf"}, std::move(collection));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
