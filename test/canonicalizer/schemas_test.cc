#include <gtest/gtest.h>
#include <jsonbinpack/canonicalizer/canonicalizer.h>
#include <jsontoolkit/json.h>

TEST(Canonicalizer, max_contains_without_contains) {
  sourcemeta::jsontoolkit::JSON document(
      "{\"type\":\"array\",\"maxContains\":2}");
  sourcemeta::jsonbinpack::canonicalizer::apply(document);
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("type"));
  EXPECT_TRUE(document["type"].is_string());
  EXPECT_EQ(document["type"], "array");
}
