#include "rules/max_contains_without_contains.cc"
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
  return bundle.apply(document);
}
