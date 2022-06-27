#include "utils.h"
#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

#include <algorithm> // std::all_of

namespace sourcemeta::jsonbinpack::canonicalizer::rules {
using namespace sourcemeta::jsontoolkit::schema::draft2020_12;
class DropNonNullKeywords final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  DropNonNullKeywords() : Rule("drop_non_null_keywords"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    if (!sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
            schema, vocabularies::validation) ||
        !schema.is_object()) {
      return false;
    }

    // If the type is set to "null" explicitly
    const bool is_null_type =
        schema.defines(keywords::validation::type) &&
        schema.at(keywords::validation::type).is_string() &&
        schema.at(keywords::validation::type).to_string() == "null";

    // If the type can only be "null" due to "enum"
    const bool is_implicit_null =
        schema.defines(keywords::validation::_enum) &&
        schema.at(keywords::validation::_enum).is_array() &&
        std::all_of(schema.at(keywords::validation::_enum).to_array().cbegin(),
                    schema.at(keywords::validation::_enum).to_array().cend(),
                    [](const auto &element) { return element.is_null(); });

    return (is_null_type || is_implicit_null) &&
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

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
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
      keywords::validation::minItems,
      keywords::validation::maxItems,
      keywords::validation::uniqueItems,
      keywords::validation::minContains,
      keywords::validation::maxContains,
      keywords::validation::minProperties,
      keywords::validation::maxProperties,
      keywords::validation::dependentRequired,
      keywords::validation::required};

  const std::set<std::string> BLACKLIST_CONTENT{
      keywords::content::contentEncoding, keywords::content::contentMediaType,
      keywords::content::contentSchema};
};
} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
