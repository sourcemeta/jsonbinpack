#ifndef SOURCEMETA_JSONTOOLKIT_JSONSCHEMA_DRAFTS_2020_12_H_
#define SOURCEMETA_JSONTOOLKIT_JSONSCHEMA_DRAFTS_2020_12_H_

#include <string> // std::string

namespace sourcemeta::jsontoolkit::schema::draft2020_12 {

namespace vocabularies {
static const std::string core{
    "https://json-schema.org/draft/2020-12/vocab/core"};
static const std::string applicator{
    "https://json-schema.org/draft/2020-12/vocab/applicator"};
static const std::string content{
    "https://json-schema.org/draft/2020-12/vocab/content"};
static const std::string validation{
    "https://json-schema.org/draft/2020-12/vocab/validation"};
static const std::string unevaluated{
    "https://json-schema.org/draft/2020-12/vocab/unevaluated"};
static const std::string format_annotation{
    "https://json-schema.org/draft/2020-12/vocab/format-annotation"};
static const std::string format_assertion{
    "https://json-schema.org/draft/2020-12/vocab/format-assertion"};
static const std::string metadata{
    "https://json-schema.org/draft/2020-12/vocab/meta-data"};
} // namespace vocabularies

namespace keywords {
namespace core {
static const std::string id{"$id"};
static const std::string vocabulary{"$vocabulary"};
static const std::string schema{"$schema"};
static const std::string comment{"$comment"};
static const std::string defs{"$defs"};
static const std::string ref{"$ref"};
static const std::string dynamicRef{"$dynamicRef"};
static const std::string anchor{"$anchor"};
static const std::string dynamicAnchor{"$dynamicAnchor"};
} // namespace core
namespace applicator {
static const std::string prefixItems{"prefixItems"};
static const std::string items{"items"};
static const std::string contains{"contains"};
static const std::string additionalProperties{"additionalProperties"};
static const std::string properties{"properties"};
static const std::string patternProperties{"patternProperties"};
static const std::string dependentSchemas{"dependentSchemas"};
static const std::string propertyNames{"propertyNames"};
static const std::string allOf{"allOf"};
static const std::string anyOf{"anyOf"};
static const std::string oneOf{"oneOf"};
static const std::string _not{"not"};
static const std::string _if{"if"};
static const std::string then{"then"};
static const std::string _else{"else"};
} // namespace applicator
namespace unevaluated {
static const std::string unevaluatedItems{"unevaluatedItems"};
static const std::string unevaluatedProperties{"unevaluatedProperties"};
} // namespace unevaluated
namespace validation {
static const std::string type{"type"};
static const std::string _const{"const"};
static const std::string _enum{"enum"};
static const std::string minimum{"minimum"};
static const std::string exclusiveMinimum{"exclusiveMinimum"};
static const std::string maximum{"maximum"};
static const std::string exclusiveMaximum{"exclusiveMaximum"};
static const std::string multipleOf{"multipleOf"};
static const std::string minLength{"minLength"};
static const std::string maxLength{"maxLength"};
static const std::string pattern{"pattern"};
static const std::string minItems{"minItems"};
static const std::string maxItems{"maxItems"};
static const std::string uniqueItems{"uniqueItems"};
static const std::string minContains{"minContains"};
static const std::string maxContains{"maxContains"};
static const std::string minProperties{"minProperties"};
static const std::string maxProperties{"maxProperties"};
static const std::string dependentRequired{"dependentRequired"};
static const std::string required{"required"};
} // namespace validation
namespace format_annotation {
static const std::string format{"format"};
} // namespace format_annotation
namespace format_assertion {
static const std::string format{"format"};
} // namespace format_assertion
namespace content {
static const std::string contentEncoding{"contentEncoding"};
static const std::string contentMediaType{"contentMediaType"};
static const std::string contentSchema{"contentSchema"};
} // namespace content
namespace metadata {
static const std::string title{"title"};
static const std::string description{"description"};
static const std::string deprecated{"deprecated"};
static const std::string readOnly{"readOnly"};
static const std::string writeOnly{"writeOnly"};
static const std::string _default{"default"};
static const std::string examples{"examples"};
} // namespace metadata
} // namespace keywords
} // namespace sourcemeta::jsontoolkit::schema::draft2020_12

#endif
