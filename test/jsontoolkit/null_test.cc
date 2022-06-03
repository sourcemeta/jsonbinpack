#include <gtest/gtest.h>
#include <jsontoolkit/json.h>
#include <stdexcept> // std::domain_error

TEST(Null, nullptr) {
  sourcemeta::jsontoolkit::JSON<std::string> document{nullptr};
  EXPECT_TRUE(document.is_null());
  EXPECT_EQ(document, nullptr);
}

TEST(Null, set_null) {
  sourcemeta::jsontoolkit::JSON<std::string> document{true};
  EXPECT_FALSE(document.is_null());
  EXPECT_EQ(document, true);
  document = nullptr;
  EXPECT_TRUE(document.is_null());
  EXPECT_EQ(document, nullptr);
}

TEST(Null, valid) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"null"};
  EXPECT_TRUE(document.is_null());
  EXPECT_EQ(document, nullptr);
}

TEST(Null, valid_with_padding) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"   null   "};
  EXPECT_TRUE(document.is_null());
  EXPECT_EQ(document, nullptr);
}

TEST(Null, more_than_needed) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"nulll"};
  EXPECT_THROW(document.is_null(), std::domain_error);
}

TEST(Null, incomplete_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"nul"};
  EXPECT_THROW(document.is_null(), std::domain_error);
}

TEST(Null, incomplete_2) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"nu"};
  EXPECT_THROW(document.is_null(), std::domain_error);
}

TEST(Null, incomplete_3) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"n"};
  EXPECT_THROW(document.is_null(), std::domain_error);
}

TEST(Null, equality_with_literal) {
  sourcemeta::jsontoolkit::JSON<std::string> left{nullptr};
  left.parse();
  sourcemeta::jsontoolkit::JSON<std::string> right{nullptr};
  right.parse();
  sourcemeta::jsontoolkit::JSON<std::string> extra{false};
  extra.parse();
  EXPECT_EQ(left, right);
  EXPECT_FALSE(left == extra);
  EXPECT_FALSE(right == extra);
}

TEST(Null, equality_with_padding) {
  sourcemeta::jsontoolkit::JSON<std::string> left{"null"};
  left.parse();
  sourcemeta::jsontoolkit::JSON<std::string> right{"  null  "};
  right.parse();
  sourcemeta::jsontoolkit::JSON<std::string> extra{"false"};
  extra.parse();
  EXPECT_EQ(left, right);
  EXPECT_FALSE(left == extra);
  EXPECT_FALSE(right == extra);
}

TEST(Null, stringify) {
  sourcemeta::jsontoolkit::JSON<std::string> document{nullptr};
  const std::string result{document.stringify()};
  EXPECT_EQ(result, "null");
}
