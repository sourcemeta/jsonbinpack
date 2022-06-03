#include <gtest/gtest.h>
#include <jsontoolkit/json.h>
#include <stdexcept>   // std::domain_error
#include <string>      // std::string
#include <type_traits> // std::is_nothrow_move_constructible
#include <utility>     // std::as_const

TEST(String, nothrow_move_constructible) {
  EXPECT_TRUE(std::is_nothrow_move_constructible<
              sourcemeta::jsontoolkit::String<std::string>>::value);
}

TEST(String, assignment_string_from_boolean) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"false"};
  EXPECT_FALSE(document.is_string());
  document = std::string{"foo"};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document, "foo");
}

TEST(String, assignment_string_from_string) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"foo\""};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document, "foo");
  document = std::string{"bar"};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document, "bar");
}

TEST(String, assignment_literal_from_boolean) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"false"};
  EXPECT_FALSE(document.is_string());
  document = "foo";
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document, "foo");
}

TEST(String, assignment_literal_from_string) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"foo\""};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document, "foo");
  document = "bar";
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document, "bar");
}

TEST(String, empty_string) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"\""};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document.size(), 0);
  EXPECT_EQ(document.to_string(), "");
  EXPECT_EQ(document, "");
  EXPECT_EQ(document, std::string{""});
}

TEST(String, parse_deep_success) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"foo\""};
  document.parse();
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document.size(), 3);
  EXPECT_EQ(document.to_string(), "foo");
  EXPECT_EQ(document, "foo");
}

TEST(String, parse_deep_failure) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"foo"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(String, parse_non_empty) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"foo\""};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document.size(), 3);
  EXPECT_EQ(document.to_string(), "foo");
  EXPECT_EQ(document, "foo");
  EXPECT_EQ(document, std::string{"foo"});
}

TEST(String, parse_padded) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"   \"foo\"    "};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document.size(), 3);
  EXPECT_EQ(document.to_string(), "foo");
}

TEST(String, parse_padded_internal) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"  foo  \""};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document.size(), 7);
  EXPECT_EQ(document.to_string(), "  foo  ");
}

TEST(String, no_right_quote) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"foo"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(String, no_left_quote) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"foo\""};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(String, no_single_quotes) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"'foo'"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(String, only_quote) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\""};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(String, escaped_quotes) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"\\\"foo\\\"\""};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document.size(), 5);
  EXPECT_EQ(document.to_string(), "\"foo\"");
}

TEST(String, escaped_reverse_solidus) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"foo\\\\bar\""};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document.size(), 7);
  EXPECT_EQ(document.to_string(), "foo\\bar");
}

TEST(String, escaped_solidus) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"foo\\/bar\""};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document.size(), 7);
  EXPECT_EQ(document.to_string(), "foo/bar");
}

TEST(String, escaped_backspace) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"foo\\bbar\""};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document.size(), 7);
  EXPECT_EQ(document.to_string(), "foo\bbar");
}

TEST(String, escaped_form_feed) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"foo\\fbar\""};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document.size(), 7);
  EXPECT_EQ(document.to_string(), "foo\fbar");
}

TEST(String, escaped_line_feed) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"foo\\nbar\""};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document.size(), 7);
  EXPECT_EQ(document.to_string(), "foo\nbar");
}

TEST(String, escaped_carriage_return) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"foo\\rbar\""};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document.size(), 7);
  EXPECT_EQ(document.to_string(), "foo\rbar");
}

TEST(String, escaped_tab) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"foo\\tbar\""};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document.size(), 7);
  EXPECT_EQ(document.to_string(), "foo\tbar");
}

TEST(String, escaped_invalid) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"foo\\xbar\""};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(String, escaped_incomplete) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"foo\\\""};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(String, invalid_with_double_quote) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"foo\"bar\""};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(String, invalid_control_characters) {
  sourcemeta::jsontoolkit::JSON<std::string> document00{"\"foo \u0000 bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document01{"\"foo \u0001 bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document02{"\"foo \u0002 bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document03{"\"foo \u0003 bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document04{"\"foo \u0004 bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document05{"\"foo \u0005 bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document06{"\"foo \u0006 bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document07{"\"foo \u0007 bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document08{"\"foo \u0008 bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document09{"\"foo \u0009 bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document0A{"\"foo \u000A bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document0B{"\"foo \u000B bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document0C{"\"foo \u000C bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document0D{"\"foo \u000D bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document0E{"\"foo \u000E bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document0F{"\"foo \u000F bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document10{"\"foo \u0010 bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document11{"\"foo \u0011 bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document12{"\"foo \u0012 bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document13{"\"foo \u0013 bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document14{"\"foo \u0014 bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document15{"\"foo \u0015 bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document16{"\"foo \u0016 bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document17{"\"foo \u0017 bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document18{"\"foo \u0018 bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document19{"\"foo \u0019 bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document1A{"\"foo \u001A bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document1B{"\"foo \u001B bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document1C{"\"foo \u001C bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document1D{"\"foo \u001D bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document1E{"\"foo \u001E bar\""};
  sourcemeta::jsontoolkit::JSON<std::string> document1F{"\"foo \u001F bar\""};

  EXPECT_THROW(document00.size(), std::domain_error);
  EXPECT_THROW(document01.size(), std::domain_error);
  EXPECT_THROW(document02.size(), std::domain_error);
  EXPECT_THROW(document03.size(), std::domain_error);
  EXPECT_THROW(document04.size(), std::domain_error);
  EXPECT_THROW(document05.size(), std::domain_error);
  EXPECT_THROW(document06.size(), std::domain_error);
  EXPECT_THROW(document07.size(), std::domain_error);
  EXPECT_THROW(document08.size(), std::domain_error);
  EXPECT_THROW(document09.size(), std::domain_error);
  EXPECT_THROW(document0A.size(), std::domain_error);
  EXPECT_THROW(document0B.size(), std::domain_error);
  EXPECT_THROW(document0C.size(), std::domain_error);
  EXPECT_THROW(document0D.size(), std::domain_error);
  EXPECT_THROW(document0E.size(), std::domain_error);
  EXPECT_THROW(document0F.size(), std::domain_error);
  EXPECT_THROW(document10.size(), std::domain_error);
  EXPECT_THROW(document11.size(), std::domain_error);
  EXPECT_THROW(document12.size(), std::domain_error);
  EXPECT_THROW(document13.size(), std::domain_error);
  EXPECT_THROW(document14.size(), std::domain_error);
  EXPECT_THROW(document15.size(), std::domain_error);
  EXPECT_THROW(document16.size(), std::domain_error);
  EXPECT_THROW(document17.size(), std::domain_error);
  EXPECT_THROW(document18.size(), std::domain_error);
  EXPECT_THROW(document19.size(), std::domain_error);
  EXPECT_THROW(document1A.size(), std::domain_error);
  EXPECT_THROW(document1B.size(), std::domain_error);
  EXPECT_THROW(document1C.size(), std::domain_error);
  EXPECT_THROW(document1D.size(), std::domain_error);
  EXPECT_THROW(document1E.size(), std::domain_error);
  EXPECT_THROW(document1F.size(), std::domain_error);
}

TEST(String, unicode_code_points) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"\\u002F\""};
  EXPECT_TRUE(document.is_string());
  EXPECT_EQ(document.size(), 1);
  EXPECT_EQ(document.to_string(), "\u002F");
}

TEST(String, unicode_code_point_equality) {
  sourcemeta::jsontoolkit::JSON<std::string> document1{"\"\\u002F\""};
  sourcemeta::jsontoolkit::JSON<std::string> document2{"\"\\u002f\""};
  sourcemeta::jsontoolkit::JSON<std::string> document3{"\"\\/\""};
  sourcemeta::jsontoolkit::JSON<std::string> document4{"\"/\""};
  EXPECT_EQ(document1.to_string(), document2.to_string());
  EXPECT_EQ(document2.to_string(), document3.to_string());
  EXPECT_EQ(document3.to_string(), document4.to_string());
}

TEST(String, invalid_code_point) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"\\uXXXX\""};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(String, invalid_lowercase_code_point) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"\\uqqqq\""};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(String, incomplete_code_point_0) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"\\u\""};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(String, incomplete_code_point_1) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"\\u6\""};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(String, incomplete_code_point_2) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"\\u2F\""};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(String, incomplete_code_point_3) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"\\u02F\""};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(String, incomplete_code_point_space) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"\\u0F 2F\""};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(String, equality_with_padding) {
  sourcemeta::jsontoolkit::JSON<std::string> left{"\"foo\""};
  left.parse();
  sourcemeta::jsontoolkit::JSON<std::string> right{"  \"foo\"  "};
  right.parse();
  sourcemeta::jsontoolkit::JSON<std::string> extra{"\"fooo\""};
  extra.parse();
  EXPECT_EQ(left, right);
  EXPECT_FALSE(left == extra);
  EXPECT_FALSE(right == extra);
}

TEST(String, stringify_empty) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"\""};
  EXPECT_EQ(document.stringify(), "\"\"");
  EXPECT_EQ(std::as_const(document).stringify(), "\"\"");
}

TEST(String, stringify_short_string) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"foo\""};
  EXPECT_EQ(document.stringify(), "\"foo\"");
  EXPECT_EQ(std::as_const(document).stringify(), "\"foo\"");
}

TEST(String, stringify_quote) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"\\\"\""};
  EXPECT_EQ(document.stringify(), "\"\\\"\"");
  EXPECT_EQ(std::as_const(document).stringify(), "\"\\\"\"");
}

TEST(String, stringify_unicode_solidus) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"\\u002F\""};
  EXPECT_EQ(document.stringify(), "\"/\"");
  EXPECT_EQ(std::as_const(document).stringify(), "\"/\"");
}

TEST(String, to_string_not_modify_result) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"foo\""};
  document.to_string()[0] = 'x';
  EXPECT_EQ(document.to_string(), "foo");
}
