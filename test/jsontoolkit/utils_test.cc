#include <gtest/gtest.h>
#include <string_view> // std::string_view
#include "../../src/jsontoolkit/src/utils.h"

TEST(utils, trim_empty_string) {
  const std::string_view input {""};
  const std::string_view result = sourcemeta::jsontoolkit::trim(input);
  EXPECT_EQ(result, "");
}

TEST(utils, trim_already_trimmed) {
  const std::string_view input {"foobar"};
  const std::string_view result = sourcemeta::jsontoolkit::trim(input);
  EXPECT_EQ(result, "foobar");
}

TEST(utils, trim_space_left) {
  const std::string_view input {"   foobar"};
  const std::string_view result = sourcemeta::jsontoolkit::trim(input);
  EXPECT_EQ(result, "foobar");
}

TEST(utils, trim_space_right) {
  const std::string_view input {"foobar  "};
  const std::string_view result = sourcemeta::jsontoolkit::trim(input);
  EXPECT_EQ(result, "foobar");
}

TEST(utils, trim_tab_left) {
  const std::string_view input {"\t\tfoobar"};
  const std::string_view result = sourcemeta::jsontoolkit::trim(input);
  EXPECT_EQ(result, "foobar");
}

TEST(utils, trim_tab_right) {
  const std::string_view input {"foobar\t\t"};
  const std::string_view result = sourcemeta::jsontoolkit::trim(input);
  EXPECT_EQ(result, "foobar");
}

TEST(utils, trim_new_line_left) {
  const std::string_view input {"\n\nfoobar"};
  const std::string_view result = sourcemeta::jsontoolkit::trim(input);
  EXPECT_EQ(result, "foobar");
}

TEST(utils, trim_new_line_right) {
  const std::string_view input {"foobar\n\n"};
  const std::string_view result = sourcemeta::jsontoolkit::trim(input);
  EXPECT_EQ(result, "foobar");
}

TEST(utils, trim_carriage_return_left) {
  const std::string_view input {"\r\rfoobar"};
  const std::string_view result = sourcemeta::jsontoolkit::trim(input);
  EXPECT_EQ(result, "foobar");
}

TEST(utils, trim_carriage_return_right) {
  const std::string_view input {"foobar\r\r"};
  const std::string_view result = sourcemeta::jsontoolkit::trim(input);
  EXPECT_EQ(result, "foobar");
}

TEST(utils, trim_audible_bell_left) {
  const std::string_view input {"\a\afoobar"};
  const std::string_view result = sourcemeta::jsontoolkit::trim(input);
  EXPECT_EQ(result, "\a\afoobar");
}

TEST(utils, trim_audible_bell_right) {
  const std::string_view input {"foobar\a\a"};
  const std::string_view result = sourcemeta::jsontoolkit::trim(input);
  EXPECT_EQ(result, "foobar\a\a");
}

TEST(utils, trim_mixed_left_right) {
  const std::string_view input {"\n \t\a \tfoobar\r\a\r\r\n   "};
  const std::string_view result = sourcemeta::jsontoolkit::trim(input);
  EXPECT_EQ(result, "\a \tfoobar\r\a");
}

TEST(utils, space_is_blank) {
  EXPECT_TRUE(sourcemeta::jsontoolkit::is_blank(' '));
  EXPECT_TRUE(sourcemeta::jsontoolkit::is_blank('\u0020'));
}

TEST(utils, carriage_return_is_blank) {
  EXPECT_TRUE(sourcemeta::jsontoolkit::is_blank('\r'));
  EXPECT_TRUE(sourcemeta::jsontoolkit::is_blank('\u000D'));
}

TEST(utils, line_feed_is_blank) {
  EXPECT_TRUE(sourcemeta::jsontoolkit::is_blank('\n'));
  EXPECT_TRUE(sourcemeta::jsontoolkit::is_blank('\u000A'));
}

TEST(utils, tab_is_blank) {
  EXPECT_TRUE(sourcemeta::jsontoolkit::is_blank('\t'));
  EXPECT_TRUE(sourcemeta::jsontoolkit::is_blank('\u0009'));
}

TEST(utils, letter_is_blank) {
  EXPECT_FALSE(sourcemeta::jsontoolkit::is_blank('a'));
}
