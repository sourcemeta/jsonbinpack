#include <gtest/gtest.h>
#include <stdexcept> // std::domain_error
#include <jsontoolkit/json.h>

TEST(String, empty_string) {
  sourcemeta::jsontoolkit::JSON document {"\"\""};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document.size(), 0);
  EXPECT_EQ(document.to_string(), "");
}

TEST(String, parse_non_empty) {
  sourcemeta::jsontoolkit::JSON document {"\"foo\""};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document.size(), 3);
  EXPECT_EQ(document.to_string(), "foo");
}

TEST(String, parse_padded) {
  sourcemeta::jsontoolkit::JSON document {"   \"foo\"    "};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document.size(), 3);
  EXPECT_EQ(document.to_string(), "foo");
}

TEST(String, parse_padded_internal) {
  sourcemeta::jsontoolkit::JSON document {"\"  foo  \""};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document.size(), 7);
  EXPECT_EQ(document.to_string(), "  foo  ");
}

TEST(String, no_right_quote) {
  sourcemeta::jsontoolkit::JSON document {"\"foo"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(String, no_left_quote) {
  sourcemeta::jsontoolkit::JSON document {"foo\""};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(String, no_single_quotes) {
  sourcemeta::jsontoolkit::JSON document {"'foo'"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(String, escaped_quotes) {
  sourcemeta::jsontoolkit::JSON document {"\"\\\"foo\\\"\""};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document.size(), 5);
  EXPECT_EQ(document.to_string(), "\"foo\"");
}

TEST(String, escaped_reverse_solidus) {
  sourcemeta::jsontoolkit::JSON document {"\"foo\\\\bar\""};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document.size(), 7);
  EXPECT_EQ(document.to_string(), "foo\\bar");
}

TEST(String, escaped_solidus) {
  sourcemeta::jsontoolkit::JSON document {"\"foo\\/bar\""};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document.size(), 7);
  EXPECT_EQ(document.to_string(), "foo/bar");
}

TEST(String, escaped_backspace) {
  sourcemeta::jsontoolkit::JSON document {"\"foo\\bbar\""};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document.size(), 7);
  EXPECT_EQ(document.to_string(), "foo\bbar");
}

TEST(String, escaped_form_feed) {
  sourcemeta::jsontoolkit::JSON document {"\"foo\\fbar\""};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document.size(), 7);
  EXPECT_EQ(document.to_string(), "foo\fbar");
}

TEST(String, escaped_line_feed) {
  sourcemeta::jsontoolkit::JSON document {"\"foo\\nbar\""};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document.size(), 7);
  EXPECT_EQ(document.to_string(), "foo\nbar");
}

TEST(String, escaped_carriage_return) {
  sourcemeta::jsontoolkit::JSON document {"\"foo\\rbar\""};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document.size(), 7);
  EXPECT_EQ(document.to_string(), "foo\rbar");
}

TEST(String, escaped_tab) {
  sourcemeta::jsontoolkit::JSON document {"\"foo\\tbar\""};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document.size(), 7);
  EXPECT_EQ(document.to_string(), "foo\tbar");
}

TEST(String, escaped_invalid) {
  sourcemeta::jsontoolkit::JSON document {"\"foo\\xbar\""};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document.size(), 8);
  EXPECT_EQ(document.to_string(), "foo\\xbar");
}

TEST(String, escaped_incomplete) {
  sourcemeta::jsontoolkit::JSON document {"\"foo\\\""};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document.size(), 4);
  EXPECT_EQ(document.to_string(), "foo\\");
}
