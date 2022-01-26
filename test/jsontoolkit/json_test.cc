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

TEST(jsontoolkit_JSON, EmptyObjectIsArray) {
  sourcemeta::jsontoolkit::JSON document{"{}"};
  EXPECT_FALSE(document.is_array());
}

TEST(jsontoolkit_JSON, EmptyArrayIsArray) {
  sourcemeta::jsontoolkit::JSON document{"[]"};
  EXPECT_TRUE(document.is_array());
}

TEST(jsontoolkit_JSON, ArrayIsStructural) {
  sourcemeta::jsontoolkit::JSON document{"[1,2,3]"};
  EXPECT_TRUE(document.is_structural());
}

TEST(jsontoolkit_JSON, ObjectIsStructural) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":2}"};
  EXPECT_TRUE(document.is_structural());
}

TEST(jsontoolkit_JSON, StringIsStructural) {
  sourcemeta::jsontoolkit::JSON document{"\"foo\""};
  EXPECT_FALSE(document.is_structural());
}

TEST(jsontoolkit_JSON, IntegerIsStructural) {
  sourcemeta::jsontoolkit::JSON document{"3"};
  EXPECT_FALSE(document.is_structural());
}

TEST(jsontoolkit_JSON, BooleanIsStructural) {
  sourcemeta::jsontoolkit::JSON document{"false"};
  EXPECT_FALSE(document.is_structural());
}

TEST(jsontoolkit_JSON, FloatIsStructural) {
  sourcemeta::jsontoolkit::JSON document{"3.14"};
  EXPECT_FALSE(document.is_structural());
}

TEST(jsontoolkit_JSON, NullIsStructural) {
  sourcemeta::jsontoolkit::JSON document{"null"};
  EXPECT_FALSE(document.is_structural());
}

TEST(jsontoolkit_JSON, TrueIsBoolean) {
  sourcemeta::jsontoolkit::JSON document{"true"};
  EXPECT_TRUE(document.is_boolean());
}

TEST(jsontoolkit_JSON, FalseIsBoolean) {
  sourcemeta::jsontoolkit::JSON document{"false"};
  EXPECT_TRUE(document.is_boolean());
}

TEST(jsontoolkit_JSON, NullIsBoolean) {
  sourcemeta::jsontoolkit::JSON document{"null"};
  EXPECT_FALSE(document.is_boolean());
}

TEST(jsontoolkit_JSON, InvalidDocument) {
  EXPECT_THROW({
    sourcemeta::jsontoolkit::JSON document{"{foo"};
  }, std::invalid_argument);
}
