#include "rules/boolean_as_enum.h"
#include "rules/boolean_schema.h"
#include "rules/content_schema_without_content_media_type.h"
#include "rules/empty_pattern_properties.h"
#include "rules/if_without_then_else.h"
#include "rules/implicit_array_lower_bound.h"
#include "rules/implicit_object_lower_bound.h"
#include "rules/implicit_object_properties.h"
#include "rules/implicit_object_required.h"
#include "rules/implicit_string_lower_bound.h"
#include "rules/implicit_type_union.h"
#include "rules/implicit_unit_multiple_of.h"
#include "rules/implied_array_unique_items.h"
#include "rules/max_contains_without_contains.h"
#include "rules/min_contains_without_contains.h"
#include "rules/min_properties_required_tautology.h"
#include "rules/then_else_without_if.h"
#include "rules/type_union_anyof.h"
#include "rules/unsatisfiable_max_contains.h"

#include <jsonbinpack/canonicalizer/bundle.h>
#include <jsonbinpack/canonicalizer/canonicalizer.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>
#include <sourcemeta/assert.h>

#include <memory> // std::make_unique

auto sourcemeta::jsonbinpack::canonicalizer::apply(
    sourcemeta::jsontoolkit::JSON<std::string> &document)
    -> sourcemeta::jsontoolkit::JSON<std::string> & {
  document.parse();
  sourcemeta::assert::CHECK(
      sourcemeta::jsontoolkit::schema::is_schema(document),
      "The input document must be a valid schema");

  using namespace sourcemeta::jsonbinpack::canonicalizer::rules;
  sourcemeta::jsonbinpack::canonicalizer::Bundle bundle;

  // Superfluous
  bundle.add(std::make_unique<ContentSchemaWithoutContentMediaType>());
  bundle.add(std::make_unique<MaxContainsWithoutContains>());
  bundle.add(std::make_unique<MinContainsWithoutContains>());
  bundle.add(std::make_unique<UnsatisfiableMaxContains>());
  bundle.add(std::make_unique<ImpliedArrayUniqueItems>());
  bundle.add(std::make_unique<MinPropertiesRequiredTautology>());
  bundle.add(std::make_unique<IfWithoutThenElse>());
  bundle.add(std::make_unique<ThenElseWithoutIf>());
  bundle.add(std::make_unique<EmptyPatternProperties>());

  // Syntax sugar
  bundle.add(std::make_unique<TypeUnionAnyOf>());
  bundle.add(std::make_unique<BooleanSchema>());
  bundle.add(std::make_unique<BooleanAsEnum>());

  // Implicits
  bundle.add(std::make_unique<ImplicitTypeUnion>());
  bundle.add(std::make_unique<ImplicitUnitMultipleOf>());
  bundle.add(std::make_unique<ImplicitArrayLowerBound>());
  bundle.add(std::make_unique<ImplicitStringLowerBound>());
  bundle.add(std::make_unique<ImplicitObjectLowerBound>());
  bundle.add(std::make_unique<ImplicitObjectRequired>());
  bundle.add(std::make_unique<ImplicitObjectProperties>());

  return bundle.apply(document);
}
