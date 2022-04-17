#include <gtest/gtest.h>
#include <jsonbinpack/canonicalizer/canonicalizer.h>
#include <jsontoolkit/json.h>

TEST(Canonicalizer, max_contains_without_contains_1) {
  sourcemeta::jsontoolkit::JSON document(R"EOF({
    "type": "array",
    "maxContains": 2
  })EOF");

  sourcemeta::jsonbinpack::canonicalizer::apply(document);

  sourcemeta::jsontoolkit::JSON expected(R"EOF({
    "type": "array"
  })EOF");

  document.parse();
  expected.parse();
  EXPECT_EQ(document, expected);
}
