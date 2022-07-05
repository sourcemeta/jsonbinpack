#include <gtest/gtest.h>
#include <jsontoolkit/json.h>
#include <sstream>   // std::ostringstream
#include <stdexcept> // std::domain_error

TEST(Boolean, true_bool) {
  sourcemeta::jsontoolkit::JSON<std::string> document{true};
  EXPECT_TRUE(document.is_boolean());
  EXPECT_TRUE(document.to_boolean());
  EXPECT_EQ(document, true);
}

TEST(Boolean, false_bool) {
  sourcemeta::jsontoolkit::JSON<std::string> document{false};
  EXPECT_TRUE(document.is_boolean());
  EXPECT_FALSE(document.to_boolean());
  EXPECT_EQ(document, false);
}

TEST(Boolean, true_string) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"true"};
  EXPECT_TRUE(document.is_boolean());
  EXPECT_TRUE(document.to_boolean());
  EXPECT_EQ(document, true);
}

TEST(Boolean, false_string) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"false"};
  EXPECT_TRUE(document.is_boolean());
  EXPECT_FALSE(document.to_boolean());
  EXPECT_EQ(document, false);
}

TEST(Boolean, true_string_padded) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"  true  "};
  EXPECT_TRUE(document.is_boolean());
  EXPECT_EQ(document, true);
}

TEST(Boolean, false_string_padded) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"  false  "};
  EXPECT_TRUE(document.is_boolean());
  EXPECT_EQ(document, false);
}

TEST(Boolean, true_more_than_needed) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"truee"};
  EXPECT_THROW(document.is_boolean(), std::domain_error);
}

TEST(Boolean, true_incomplete_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"tru"};
  EXPECT_THROW(document.is_boolean(), std::domain_error);
}

TEST(Boolean, true_incomplete_2) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"tr"};
  EXPECT_THROW(document.is_boolean(), std::domain_error);
}

TEST(Boolean, true_incomplete_3) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"t"};
  EXPECT_THROW(document.is_boolean(), std::domain_error);
}

TEST(Boolean, false_more_than_needed) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"falsee"};
  EXPECT_THROW(document.is_boolean(), std::domain_error);
}

TEST(Boolean, false_incomplete_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"fals"};
  EXPECT_THROW(document.is_boolean(), std::domain_error);
}

TEST(Boolean, false_incomplete_2) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"fal"};
  EXPECT_THROW(document.is_boolean(), std::domain_error);
}

TEST(Boolean, false_incomplete_3) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"fa"};
  EXPECT_THROW(document.is_boolean(), std::domain_error);
}

TEST(Boolean, false_incomplete_4) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"f"};
  EXPECT_THROW(document.is_boolean(), std::domain_error);
}

TEST(Boolean, false_literal_equality) {
  sourcemeta::jsontoolkit::JSON<std::string> left{false};
  left.parse();
  sourcemeta::jsontoolkit::JSON<std::string> right{false};
  right.parse();
  sourcemeta::jsontoolkit::JSON<std::string> extra{true};
  extra.parse();
  EXPECT_EQ(left, right);
  EXPECT_FALSE(left == extra);
  EXPECT_FALSE(right == extra);
}

TEST(Boolean, true_literal_equality) {
  sourcemeta::jsontoolkit::JSON<std::string> left{true};
  left.parse();
  sourcemeta::jsontoolkit::JSON<std::string> right{true};
  right.parse();
  sourcemeta::jsontoolkit::JSON<std::string> extra{false};
  extra.parse();
  EXPECT_EQ(left, right);
  EXPECT_FALSE(left == extra);
  EXPECT_FALSE(right == extra);
}

TEST(Boolean, false_equality_with_padding) {
  sourcemeta::jsontoolkit::JSON<std::string> left{"false"};
  left.parse();
  sourcemeta::jsontoolkit::JSON<std::string> right{"  false  "};
  right.parse();
  sourcemeta::jsontoolkit::JSON<std::string> extra{"true"};
  extra.parse();
  EXPECT_EQ(left, right);
  EXPECT_FALSE(left == extra);
  EXPECT_FALSE(right == extra);
}

TEST(Boolean, true_equality_with_padding) {
  sourcemeta::jsontoolkit::JSON<std::string> left{"true"};
  left.parse();
  sourcemeta::jsontoolkit::JSON<std::string> right{"  true  "};
  right.parse();
  sourcemeta::jsontoolkit::JSON<std::string> extra{"false"};
  extra.parse();
  EXPECT_EQ(left, right);
  EXPECT_FALSE(left == extra);
  EXPECT_FALSE(right == extra);
}

TEST(Boolean, stringify_false) {
  sourcemeta::jsontoolkit::JSON<std::string> document{false};
  std::ostringstream stream;
  stream << document;
  EXPECT_EQ(stream.str(), "false");
}

TEST(Boolean, stringify_true) {
  sourcemeta::jsontoolkit::JSON<std::string> document{true};
  std::ostringstream stream;
  stream << document;
  EXPECT_EQ(stream.str(), "true");
}
