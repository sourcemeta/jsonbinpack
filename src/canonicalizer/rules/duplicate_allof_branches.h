namespace sourcemeta::jsonbinpack::canonicalizer {

/// @ingroup canonicalizer_rules_simplification
///
/// ### JSON Schema 2020-12
///
/// | Vocabulary URI                                         | Required |
/// |--------------------------------------------------------|----------|
/// | https://json-schema.org/draft/2020-12/vocab/applicator | Y        |
///
/// The `allOf` keyword from the Applicator vocabulary represents a logical
/// conjunction. As such, duplicate branches do not affect the result and can be
/// removed.
///
/// \f[\frac{allOf \in dom(S) \land \#S.allOf \neq \#\{ x \mid S.allOf \}}{S
/// \mapsto S \cup \{ allOf \mapsto seq \; \{ x \mid S.allOf \} \} }\f]

class DuplicateAllOfBranches final
    : public sourcemeta::jsontoolkit::SchemaTransformRule {
public:
  DuplicateAllOfBranches() : SchemaTransformRule("duplicate_allof_branches"){};

  /// The rule condition
  [[nodiscard]] auto condition(const sourcemeta::jsontoolkit::JSON &schema,
                               const std::string &dialect,
                               const std::set<std::string> &vocabularies,
                               const sourcemeta::jsontoolkit::Pointer &) const
      -> bool override {
    return dialect == "https://json-schema.org/draft/2020-12/schema" &&
           vocabularies.contains(
               "https://json-schema.org/draft/2020-12/vocab/applicator") &&
           schema.is_object() && schema.defines("allOf") &&
           schema.at("allOf").is_array() && !is_unique(schema.at("allOf"));
  }

  /// The rule transformation
  auto transform(sourcemeta::jsontoolkit::SchemaTransformer &transformer) const
      -> void override {
    auto collection = transformer.schema().at("allOf");
    std::sort(collection.as_array().begin(), collection.as_array().end());
    auto last =
        std::unique(collection.as_array().begin(), collection.as_array().end());
    collection.erase(last, collection.as_array().end());
    transformer.replace({"allOf"}, std::move(collection));
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer
