namespace sourcemeta::jsonbinpack::canonicalizer {

class DropNonStringKeywords final : public sourcemeta::alterschema::Rule {
public:
  DropNonStringKeywords() : Rule("drop_non_string_keywords"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           schema.is_object() && schema.defines(keywords::validation::type) &&
           schema.at(keywords::validation::type).is_string() &&
           schema.at(keywords::validation::type).to_string() == "string" &&
           (defines_any_keyword_from_set(schema, vocabularies::applicator,
                                         BLACKLIST_APPLICATOR) ||
            defines_any_keyword_from_set(schema, vocabularies::unevaluated,
                                         BLACKLIST_UNEVALUATED) ||
            defines_any_keyword_from_set(schema, vocabularies::validation,
                                         BLACKLIST_VALIDATION));
  }

  auto transform(sourcemeta::jsontoolkit::JSON &document,
                 sourcemeta::jsontoolkit::Value &value) const -> void override {
    std::set<std::string> keywords_to_remove{};
    auto inserter =
        std::inserter(keywords_to_remove, keywords_to_remove.begin());
    copy_extra_keywords(schema, vocabularies::applicator, BLACKLIST_APPLICATOR,
                        inserter);
    copy_extra_keywords(schema, vocabularies::unevaluated,
                        BLACKLIST_UNEVALUATED, inserter);
    copy_extra_keywords(schema, vocabularies::validation, BLACKLIST_VALIDATION,
                        inserter);
    for (const auto &keyword : keywords_to_remove) {
      schema.erase(keyword);
    }
  }

private:
  const std::set<std::string> BLACKLIST_APPLICATOR{
      keywords::applicator::prefixItems,
      keywords::applicator::items,
      keywords::applicator::contains,
      keywords::applicator::additionalProperties,
      keywords::applicator::properties,
      keywords::applicator::patternProperties,
      keywords::applicator::dependentSchemas,
      keywords::applicator::propertyNames};

  const std::set<std::string> BLACKLIST_UNEVALUATED{
      keywords::unevaluated::unevaluatedItems,
      keywords::unevaluated::unevaluatedProperties};

  const std::set<std::string> BLACKLIST_VALIDATION{
      keywords::validation::minimum,
      keywords::validation::exclusiveMinimum,
      keywords::validation::maximum,
      keywords::validation::exclusiveMaximum,
      keywords::validation::multipleOf,
      keywords::validation::minItems,
      keywords::validation::maxItems,
      keywords::validation::uniqueItems,
      keywords::validation::minContains,
      keywords::validation::maxContains,
      keywords::validation::minProperties,
      keywords::validation::maxProperties,
      keywords::validation::dependentRequired,
      keywords::validation::required};
};
} // namespace sourcemeta::jsonbinpack::canonicalizer
