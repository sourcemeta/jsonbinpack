#include <gtest/gtest.h>
#include <jsontoolkit/json.h>
#include <stdexcept> // std::domain_error

TEST(Null, nullptr) {
  sourcemeta::jsontoolkit::JSON document{nullptr};
  EXPECT_TRUE(document.is_null());
  EXPECT_EQ(document, nullptr);
}

TEST(Null, set_null) {
  sourcemeta::jsontoolkit::JSON document{true};
  EXPECT_FALSE(document.is_null());
  EXPECT_EQ(document, true);
  document = nullptr;
  EXPECT_TRUE(document.is_null());
  EXPECT_EQ(document, nullptr);
}

TEST(Null, valid) {
  sourcemeta::jsontoolkit::JSON document{"null"};
  EXPECT_TRUE(document.is_null());
  EXPECT_EQ(document, nullptr);
}

TEST(Null, valid_with_padding) {
  sourcemeta::jsontoolkit::JSON document{"   null   "};
  EXPECT_TRUE(document.is_null());
  EXPECT_EQ(document, nullptr);
}

TEST(Null, more_than_needed) {
  sourcemeta::jsontoolkit::JSON document{"nulll"};
  EXPECT_THROW(document.is_null(), std::domain_error);
}

TEST(Null, incomplete_1) {
  sourcemeta::jsontoolkit::JSON document{"nul"};
  EXPECT_THROW(document.is_null(), std::domain_error);
}

TEST(Null, incomplete_2) {
  sourcemeta::jsontoolkit::JSON document{"nu"};
  EXPECT_THROW(document.is_null(), std::domain_error);
}

TEST(Null, incomplete_3) {
  sourcemeta::jsontoolkit::JSON document{"n"};
  EXPECT_THROW(document.is_null(), std::domain_error);
}

TEST(Null, equality_with_literal) {
  sourcemeta::jsontoolkit::JSON left{nullptr};
  left.parse();
  sourcemeta::jsontoolkit::JSON right{nullptr};
  right.parse();
  sourcemeta::jsontoolkit::JSON extra{false};
  extra.parse();
  EXPECT_EQ(left, right);
  EXPECT_FALSE(left == extra);
  EXPECT_FALSE(right == extra);
}

TEST(Null, equality_with_padding) {
  sourcemeta::jsontoolkit::JSON left{"null"};
  left.parse();
  sourcemeta::jsontoolkit::JSON right{"  null  "};
  right.parse();
  sourcemeta::jsontoolkit::JSON extra{"false"};
  extra.parse();
  EXPECT_EQ(left, right);
  EXPECT_FALSE(left == extra);
  EXPECT_FALSE(right == extra);
}

TEST(Null, stringify) {
  sourcemeta::jsontoolkit::JSON document{nullptr};
  const std::string result{document.stringify()};
  EXPECT_EQ(result, "null");
}
