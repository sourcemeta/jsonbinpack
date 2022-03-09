#include <gtest/gtest.h>
#include <jsontoolkit/json.h>

TEST(Object, empty_object_string) {
  sourcemeta::jsontoolkit::JSON document{"{}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 0);
}
