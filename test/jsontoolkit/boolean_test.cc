#include <gtest/gtest.h>
#include <jsontoolkit/json.h>
#include <stdexcept> // std::domain_error

TEST(Boolean, true_bool) {
  sourcemeta::jsontoolkit::JSON document{true};
  EXPECT_TRUE(document.is_boolean());
  EXPECT_TRUE(document.to_boolean());
}

TEST(Boolean, false_bool) {
  sourcemeta::jsontoolkit::JSON document{false};
  EXPECT_TRUE(document.is_boolean());
  EXPECT_FALSE(document.to_boolean());
}

TEST(Boolean, true_string) {
  sourcemeta::jsontoolkit::JSON document{"true"};
  EXPECT_TRUE(document.is_boolean());
  EXPECT_TRUE(document.to_boolean());
}

TEST(Boolean, false_string) {
  sourcemeta::jsontoolkit::JSON document{"false"};
  EXPECT_TRUE(document.is_boolean());
  EXPECT_FALSE(document.to_boolean());
}

TEST(Boolean, true_string_padded) {
  sourcemeta::jsontoolkit::JSON document{"  true  "};
  EXPECT_TRUE(document.is_boolean());
  EXPECT_TRUE(document.to_boolean());
}

TEST(Boolean, false_string_padded) {
  sourcemeta::jsontoolkit::JSON document{"  false  "};
  EXPECT_TRUE(document.is_boolean());
  EXPECT_FALSE(document.to_boolean());
}

TEST(Boolean, true_more_than_needed) {
  sourcemeta::jsontoolkit::JSON document{"truee"};
  EXPECT_THROW(document.is_boolean(), std::domain_error);
}

TEST(Boolean, true_incomplete_1) {
  sourcemeta::jsontoolkit::JSON document{"tru"};
  EXPECT_THROW(document.is_boolean(), std::domain_error);
}

TEST(Boolean, true_incomplete_2) {
  sourcemeta::jsontoolkit::JSON document{"tr"};
  EXPECT_THROW(document.is_boolean(), std::domain_error);
}

TEST(Boolean, true_incomplete_3) {
  sourcemeta::jsontoolkit::JSON document{"t"};
  EXPECT_THROW(document.is_boolean(), std::domain_error);
}

TEST(Boolean, false_more_than_needed) {
  sourcemeta::jsontoolkit::JSON document{"falsee"};
  EXPECT_THROW(document.is_boolean(), std::domain_error);
}

TEST(Boolean, false_incomplete_1) {
  sourcemeta::jsontoolkit::JSON document{"fals"};
  EXPECT_THROW(document.is_boolean(), std::domain_error);
}

TEST(Boolean, false_incomplete_2) {
  sourcemeta::jsontoolkit::JSON document{"fal"};
  EXPECT_THROW(document.is_boolean(), std::domain_error);
}

TEST(Boolean, false_incomplete_3) {
  sourcemeta::jsontoolkit::JSON document{"fa"};
  EXPECT_THROW(document.is_boolean(), std::domain_error);
}

TEST(Boolean, false_incomplete_4) {
  sourcemeta::jsontoolkit::JSON document{"f"};
  EXPECT_THROW(document.is_boolean(), std::domain_error);
}
