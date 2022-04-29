#include "rules/content_schema_without_content_media_type.h"
#include "rules/empty_pattern_properties.h"
#include "rules/if_without_then_else.h"
#include "rules/implied_array_unique_items.h"
#include "rules/max_contains_without_contains.h"
#include "rules/min_properties_required_tautology.h"
#include "rules/then_else_without_if.h"
#include "rules/unsatisfiable_max_contains.h"
#include <jsonbinpack/canonicalizer/bundle.h>
#include <jsonbinpack/canonicalizer/canonicalizer.h>
#include <jsontoolkit/json.h>
#include <memory> // std::make_unique

auto sourcemeta::jsonbinpack::canonicalizer::apply(
    sourcemeta::jsontoolkit::JSON &document)
    -> sourcemeta::jsontoolkit::JSON & {
  sourcemeta::jsonbinpack::canonicalizer::Bundle bundle;
  bundle.add(std::make_unique<sourcemeta::jsonbinpack::canonicalizer::rules::
                                  MaxContainsWithoutContains>());
  bundle.add(std::make_unique<sourcemeta::jsonbinpack::canonicalizer::rules::
                                  ContentSchemaWithoutContentMediaType>());
  bundle.add(std::make_unique<sourcemeta::jsonbinpack::canonicalizer::rules::
                                  UnsatisfiableMaxContains>());
  bundle.add(std::make_unique<sourcemeta::jsonbinpack::canonicalizer::rules::
                                  ImpliedArrayUniqueItems>());
  bundle.add(std::make_unique<sourcemeta::jsonbinpack::canonicalizer::rules::
                                  MinPropertiesRequiredTautology>());
  bundle.add(
      std::make_unique<
          sourcemeta::jsonbinpack::canonicalizer::rules::IfWithoutThenElse>());
  bundle.add(
      std::make_unique<
          sourcemeta::jsonbinpack::canonicalizer::rules::ThenElseWithoutIf>());
  bundle.add(std::make_unique<sourcemeta::jsonbinpack::canonicalizer::rules::
                                  EmptyPatternProperties>());
  return bundle.apply(document);
}
