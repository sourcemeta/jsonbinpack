#ifndef SOURCEMETA_JSONTOOLKIT_JSONSCHEMA_DRAFTS_2020_12_H_
#define SOURCEMETA_JSONTOOLKIT_JSONSCHEMA_DRAFTS_2020_12_H_

#include <string> // std::string

namespace sourcemeta::jsontoolkit::schema::draft2020_12 {

namespace vocabularies {
const std::string core{"https://json-schema.org/draft/2020-12/vocab/core"};
const std::string applicator{
    "https://json-schema.org/draft/2020-12/vocab/applicator"};
const std::string content{
    "https://json-schema.org/draft/2020-12/vocab/content"};
const std::string validation{
    "https://json-schema.org/draft/2020-12/vocab/validation"};
const std::string unevaluated{
    "https://json-schema.org/draft/2020-12/vocab/unevaluated"};
const std::string format_annotation{
    "https://json-schema.org/draft/2020-12/vocab/format-annotation"};
const std::string format_assertion{
    "https://json-schema.org/draft/2020-12/vocab/format-assertion"};
const std::string metadata{
    "https://json-schema.org/draft/2020-12/vocab/meta-data"};
} // namespace vocabularies

namespace keywords {
namespace core {
const std::string id{"$id"};
const std::string vocabulary{"$vocabulary"};
const std::string schema{"$schema"};
const std::string comment{"$comment"};
const std::string defs{"$defs"};
const std::string ref{"$ref"};
const std::string dynamicRef{"$dynamicRef"};
const std::string anchor{"$anchor"};
const std::string dynamicAnchor{"$dynamicAnchor"};
} // namespace core
namespace applicator {
const std::string prefixItems{"prefixItems"};
const std::string items{"items"};
const std::string contains{"contains"};
const std::string additionalProperties{"additionalProperties"};
const std::string properties{"properties"};
const std::string patternProperties{"patternProperties"};
const std::string dependentSchemas{"dependentSchemas"};
const std::string propertyNames{"propertyNames"};
const std::string allOf{"allOf"};
const std::string anyOf{"anyOf"};
const std::string oneOf{"oneOf"};
const std::string _not{"not"};
const std::string _if{"if"};
const std::string then{"then"};
const std::string _else{"else"};
} // namespace applicator
namespace unevaluated {
const std::string unevaluatedItems{"unevaluatedItems"};
const std::string unevaluatedProperties{"unevaluatedProperties"};
} // namespace unevaluated
namespace validation {
const std::string type{"type"};
const std::string _const{"const"};
const std::string _enum{"enum"};
const std::string minimum{"minimum"};
const std::string exclusiveMinimum{"exclusiveMinimum"};
const std::string maximum{"maximum"};
const std::string exclusiveMaximum{"exclusiveMaximum"};
const std::string multipleOf{"multipleOf"};
const std::string minLength{"minLength"};
const std::string maxLength{"maxLength"};
const std::string pattern{"pattern"};
const std::string minItems{"minItems"};
const std::string maxItems{"maxItems"};
const std::string uniqueItems{"uniqueItems"};
const std::string minContains{"minContains"};
const std::string maxContains{"maxContains"};
const std::string minProperties{"minProperties"};
const std::string maxProperties{"maxProperties"};
const std::string dependentRequired{"dependentRequired"};
const std::string required{"required"};
} // namespace validation
namespace format_annotation {
const std::string format{"format"};
} // namespace format_annotation
namespace format_assertion {
const std::string format{"format"};
} // namespace format_assertion
namespace content {
const std::string contentEncoding{"contentEncoding"};
const std::string contentMediaType{"contentMediaType"};
const std::string contentSchema{"contentSchema"};
} // namespace content
namespace metadata {
const std::string title{"title"};
const std::string description{"description"};
const std::string deprecated{"deprecated"};
const std::string readOnly{"readOnly"};
const std::string writeOnly{"writeOnly"};
const std::string _default{"default"};
const std::string examples{"examples"};
} // namespace metadata
} // namespace keywords
} // namespace sourcemeta::jsontoolkit::schema::draft2020_12

#endif
