#ifndef SOURCEMETA_JSONBINPACK_CANONICALIZER_APPLICATORS_H_
#define SOURCEMETA_JSONBINPACK_CANONICALIZER_APPLICATORS_H_

#include <alterschema/applicator.h>
#include <jsontoolkit/schema.h>

#include <vector> // std::vector

namespace sourcemeta::jsonbinpack::canonicalizer {

// For readability
using Type = sourcemeta::alterschema::ApplicatorType;
using namespace sourcemeta::jsontoolkit::schema::draft2020_12;

const std::vector<sourcemeta::alterschema::Applicator> applicators{
    {vocabularies::core, keywords::core::defs, Type::Object},
    {vocabularies::content, keywords::content::contentSchema, Type::Value},
    {vocabularies::unevaluated, keywords::unevaluated::unevaluatedItems,
     Type::Value},
    {vocabularies::unevaluated, keywords::unevaluated::unevaluatedProperties,
     Type::Value},
    {vocabularies::applicator, keywords::applicator::dependentSchemas,
     Type::Object},
    {vocabularies::applicator, keywords::applicator::properties, Type::Object},
    {vocabularies::applicator, keywords::applicator::patternProperties,
     Type::Object},
    {vocabularies::applicator, keywords::applicator::prefixItems, Type::Array},
    {vocabularies::applicator, keywords::applicator::allOf, Type::Array},
    {vocabularies::applicator, keywords::applicator::anyOf, Type::Array},
    {vocabularies::applicator, keywords::applicator::oneOf, Type::Array},
    {vocabularies::applicator, keywords::applicator::items, Type::Value},
    {vocabularies::applicator, keywords::applicator::additionalProperties,
     Type::Value},
    {vocabularies::applicator, keywords::applicator::contains, Type::Value},
    {vocabularies::applicator, keywords::applicator::propertyNames,
     Type::Value},
    {vocabularies::applicator, keywords::applicator::_not, Type::Value},
    {vocabularies::applicator, keywords::applicator::_if, Type::Value},
    {vocabularies::applicator, keywords::applicator::then, Type::Value},
    {vocabularies::applicator, keywords::applicator::_else, Type::Value}};

} // namespace sourcemeta::jsonbinpack::canonicalizer

#endif
