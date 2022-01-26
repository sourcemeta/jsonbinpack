#include <gtest/gtest.h>
#include <stdexcept>
#include <jsontoolkit/json.h>

TEST(jsontoolkit_JSON, EmptyObjectIsObject) {
  sourcemeta::jsontoolkit::JSON document{"{}"};
  EXPECT_TRUE(document.is_object());
}

TEST(jsontoolkit_JSON, EmptyArrayIsObject) {
  sourcemeta::jsontoolkit::JSON document{"[]"};
  EXPECT_FALSE(document.is_object());
}

TEST(jsontoolkit_JSON, InvalidDocument) {
  EXPECT_THROW({
    sourcemeta::jsontoolkit::JSON document{"{foo"};
  }, std::invalid_argument);
}
