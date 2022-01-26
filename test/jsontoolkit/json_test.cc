#include <gtest/gtest.h>
#include <jsontoolkit/json.h>

TEST(JSON, EmptyObjectIsObject) {
  sourcemeta::jsontoolkit::JSON document{"{}"};
  EXPECT_TRUE(document.is_object());
}

TEST(JSON, EmptyArrayIsObject) {
  sourcemeta::jsontoolkit::JSON document{"[]"};
  EXPECT_FALSE(document.is_object());
}
