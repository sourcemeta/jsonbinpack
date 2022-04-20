#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

/**
 * schema.maxContains? && !schema.contains? => schema \ { maxContains }
 */

// TODO: Rules should also check what vocabulary its currently in use.
// We can approximate this my creating a
// sourcemeta::jsontoolkit::JSONSchema::has_vocabulary(); function that returns
// true for all known vocabularies at the moment?

class MaxContainsWithoutContains final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  MaxContainsWithoutContains() : Rule("MaxContainsWithoutContains"){};
  auto condition(sourcemeta::jsontoolkit::JSON &schema) -> bool override {
    return schema.contains("maxContains") && !schema.contains("contains");
  }

  auto transform(sourcemeta::jsontoolkit::JSON &schema) -> void override {
    schema.erase("maxContains");
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
