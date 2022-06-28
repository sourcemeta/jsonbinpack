#include "utils.h"
#include <alterschema/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::canonicalizer::rules {
using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
class DropNonNumericKeywords final
    : public sourcemeta::alterschema::Rule<std::string> {
public:
  DropNonNumericKeywords() : Rule("drop_non_numeric_keywords"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    if (!sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
            schema, vocabularies::validation) ||
        !schema.is_object() || !schema.defines(keywords::validation::type) ||
        !schema.at(keywords::validation::type).is_string()) {
      return false;
    }

    if (schema.at(keywords::validation::type).to_string() != "number" &&
        schema.at(keywords::validation::type).to_string() != "integer") {
      return false;
    }

    return defines_any_keyword_from_set(schema, vocabularies::applicator,
                                        BLACKLIST_APPLICATOR) ||
           defines_any_keyword_from_set(schema, vocabularies::unevaluated,
                                        BLACKLIST_UNEVALUATED) ||
           defines_any_keyword_from_set(schema, vocabularies::validation,
                                        BLACKLIST_VALIDATION) ||
           defines_any_keyword_from_set(schema, vocabularies::format_annotation,
                                        BLACKLIST_FORMAT_ANNOTATION) ||
           defines_any_keyword_from_set(schema, vocabularies::format_assertion,
                                        BLACKLIST_FORMAT_ASSERTION) ||
           defines_any_keyword_from_set(schema, vocabularies::content,
                                        BLACKLIST_CONTENT);
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    std::set<std::string> keywords_to_remove{};
    auto inserter =
        std::inserter(keywords_to_remove, keywords_to_remove.begin());
    copy_extra_keywords(schema, vocabularies::applicator, BLACKLIST_APPLICATOR,
                        inserter);
    copy_extra_keywords(schema, vocabularies::unevaluated,
                        BLACKLIST_UNEVALUATED, inserter);
    copy_extra_keywords(schema, vocabularies::validation, BLACKLIST_VALIDATION,
                        inserter);
    copy_extra_keywords(schema, vocabularies::format_annotation,
                        BLACKLIST_FORMAT_ANNOTATION, inserter);
    copy_extra_keywords(schema, vocabularies::format_annotation,
                        BLACKLIST_FORMAT_ASSERTION, inserter);
    copy_extra_keywords(schema, vocabularies::content, BLACKLIST_CONTENT,
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
      keywords::validation::minLength,
      keywords::validation::maxLength,
      keywords::validation::pattern,
      keywords::validation::minItems,
      keywords::validation::maxItems,
      keywords::validation::uniqueItems,
      keywords::validation::minContains,
      keywords::validation::maxContains,
      keywords::validation::minProperties,
      keywords::validation::maxProperties,
      keywords::validation::dependentRequired,
      keywords::validation::required};

  const std::set<std::string> BLACKLIST_FORMAT_ANNOTATION{
      keywords::format_annotation::format};

  const std::set<std::string> BLACKLIST_FORMAT_ASSERTION{
      keywords::format_assertion::format};

  const std::set<std::string> BLACKLIST_CONTENT{
      keywords::content::contentEncoding, keywords::content::contentMediaType,
      keywords::content::contentSchema};
};
} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
