namespace sourcemeta::jsonbinpack::canonicalizer {

class DropNonArrayKeywords final : public sourcemeta::alterschema::Rule {
public:
  DropNonArrayKeywords() : Rule("drop_non_array_keywords"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool override {
    return sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
               schema, vocabularies::validation) &&
           schema.is_object() && schema.defines(keywords::validation::type) &&
           schema.at(keywords::validation::type).is_string() &&
           schema.at(keywords::validation::type).to_string() == "array" &&
           (defines_any_keyword_from_set(schema, vocabularies::applicator,
                                         BLACKLIST_APPLICATOR) ||
            defines_any_keyword_from_set(schema, vocabularies::unevaluated,
                                         BLACKLIST_UNEVALUATED) ||
            defines_any_keyword_from_set(schema,
                                         vocabularies::format_annotation,
                                         BLACKLIST_FORMAT_ANNOTATION) ||
            defines_any_keyword_from_set(schema, vocabularies::format_assertion,
                                         BLACKLIST_FORMAT_ASSERTION) ||
            defines_any_keyword_from_set(schema, vocabularies::validation,
                                         BLACKLIST_VALIDATION) ||
            defines_any_keyword_from_set(schema, vocabularies::content,
                                         BLACKLIST_CONTENT));
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
    copy_extra_keywords(schema, vocabularies::format_annotation,
                        BLACKLIST_FORMAT_ANNOTATION, inserter);
    copy_extra_keywords(schema, vocabularies::format_assertion,
                        BLACKLIST_FORMAT_ASSERTION, inserter);
    copy_extra_keywords(schema, vocabularies::validation, BLACKLIST_VALIDATION,
                        inserter);
    copy_extra_keywords(schema, vocabularies::content, BLACKLIST_CONTENT,
                        inserter);
    for (const auto &keyword : keywords_to_remove) {
      schema.erase(keyword);
    }
  }

private:
  const std::set<std::string> BLACKLIST_APPLICATOR{
      keywords::applicator::additionalProperties,
      keywords::applicator::properties, keywords::applicator::patternProperties,
      keywords::applicator::dependentSchemas,
      keywords::applicator::propertyNames};

  const std::set<std::string> BLACKLIST_UNEVALUATED{
      keywords::unevaluated::unevaluatedProperties};

  const std::set<std::string> BLACKLIST_FORMAT_ANNOTATION{
      keywords::format_annotation::format};
  const std::set<std::string> BLACKLIST_FORMAT_ASSERTION{
      keywords::format_assertion::format};

  const std::set<std::string> BLACKLIST_VALIDATION{
      keywords::validation::minimum,
      keywords::validation::exclusiveMinimum,
      keywords::validation::maximum,
      keywords::validation::exclusiveMaximum,
      keywords::validation::multipleOf,
      keywords::validation::minLength,
      keywords::validation::maxLength,
      keywords::validation::pattern,
      keywords::validation::minProperties,
      keywords::validation::maxProperties,
      keywords::validation::dependentRequired,
      keywords::validation::required};

  const std::set<std::string> BLACKLIST_CONTENT{
      keywords::content::contentEncoding, keywords::content::contentMediaType,
      keywords::content::contentSchema};
};
} // namespace sourcemeta::jsonbinpack::canonicalizer