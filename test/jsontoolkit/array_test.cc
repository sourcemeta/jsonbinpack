#include <gtest/gtest.h>
#include <jsontoolkit/json.h>
#include <sstream>   // std::ostringstream
#include <stdexcept> // std::domain_error
#include <utility>   // std::as_const

TEST(Array, empty_array_string) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 0);
}

TEST(Array, empty_array_with_inner_space) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[        ]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 0);
}

TEST(Array, empty_array_incomplete_right) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"["};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Array, empty_array_incomplete_right_with_inner_space) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[  "};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Array, empty_with_comma) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[,]"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Array, empty_with_comma_and_no_right_bracket) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[,"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Array, empty_with_comma_and_spacing) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[   ,   ]"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Array, parse_deep_success) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[true]"};
  document.parse();
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_EQ(document.at(0).to_boolean(), true);
}

TEST(Array, parse_deep_failure) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[true"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(Array, parse_deep_failure_in_item) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[tru]"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(Array, parse_is_lazy) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[x,x]"};
  // Would throw otherwise
  EXPECT_EQ(document.size(), 2);
}

TEST(Array, array_without_comma_after_element) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[1[2]]"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(Array, unclosed_string_element) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[\"foo]"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(Array, single_element) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[true]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_EQ(document.at(0).to_boolean(), true);
}

TEST(Array, single_element_with_inner_space) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[   true    ]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_EQ(document.at(0).to_boolean(), true);
}

TEST(Array, single_element_with_padding) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"   [ true ]   "};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_EQ(document.at(0).to_boolean(), true);
}

TEST(Array, two_elements_with_spacing) {
  sourcemeta::jsontoolkit::JSON<std::string> document{
      "[   true  ,   false   ]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 2);
  EXPECT_EQ(document.at(0).to_boolean(), true);
  EXPECT_EQ(document.at(1).to_boolean(), false);
}

TEST(Array, single_element_trailing_comma) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[true,]"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Array, single_element_trailing_commas) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[true,,,]"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Array, single_element_middle_comma) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[true,,true]"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Array, single_element_leading_comma) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[,true]"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Array, single_element_leading_commas) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[,,,true]"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Array, concat_array) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[true][false]"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Array, concat_array_middle_comma) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[true],[false]"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Array, concat_array_middle_unbalanced_left) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[true],false]"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Array, concat_array_middle_unbalanced_right) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[true,[false]"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Array, one_level_nested_array) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[[true],false]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document.at(0).is_array());
  EXPECT_TRUE(document.at(1).is_boolean());
  EXPECT_EQ(document.at(0).size(), 1);
  EXPECT_TRUE(document.at(0).at(0).is_boolean());
  EXPECT_TRUE(document.at(0).at(0).to_boolean());
  EXPECT_FALSE(document.at(1).to_boolean());
}

TEST(Array, one_level_nested_array_with_padding) {
  sourcemeta::jsontoolkit::JSON<std::string> document{
      "  [ [  true ]  ,  false  ]   "};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document.at(0).is_array());
  EXPECT_TRUE(document.at(1).is_boolean());
  EXPECT_EQ(document.at(0).size(), 1);
  EXPECT_TRUE(document.at(0).at(0).is_boolean());
  EXPECT_TRUE(document.at(0).at(0).to_boolean());
  EXPECT_FALSE(document.at(1).to_boolean());
}

TEST(Array, two_levels_nested_array) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[true,[false,[true]]]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document.at(0).is_boolean());
  EXPECT_TRUE(document.at(0).to_boolean());
  EXPECT_TRUE(document.at(1).is_array());
  EXPECT_EQ(document.at(1).size(), 2);
  EXPECT_TRUE(document.at(1).at(0).is_boolean());
  EXPECT_FALSE(document.at(1).at(0).to_boolean());
  EXPECT_TRUE(document.at(1).at(1).is_array());
  EXPECT_EQ(document.at(1).at(1).size(), 1);
  EXPECT_TRUE(document.at(1).at(1).at(0).is_boolean());
  EXPECT_TRUE(document.at(1).at(1).at(0).to_boolean());
}

TEST(Array, two_levels_nested_array_clear) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[true,[false,[true]]]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 2);
  document.clear();
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 0);
}

TEST(Array, two_levels_nested_array_clear_non_parsed) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[true,[false,[true]]]"};
  document.clear();
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 0);
}

TEST(Array, two_levels_nested_array_with_padding) {
  sourcemeta::jsontoolkit::JSON<std::string> document{
      "  [  true , [  false  , [ true ]  ]  ] "};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document.at(0).is_boolean());
  EXPECT_TRUE(document.at(0).to_boolean());
  EXPECT_TRUE(document.at(1).is_array());
  EXPECT_EQ(document.at(1).size(), 2);
  EXPECT_TRUE(document.at(1).at(0).is_boolean());
  EXPECT_FALSE(document.at(1).at(0).to_boolean());
  EXPECT_TRUE(document.at(1).at(1).is_array());
  EXPECT_EQ(document.at(1).at(1).size(), 1);
  EXPECT_TRUE(document.at(1).at(1).at(0).is_boolean());
  EXPECT_TRUE(document.at(1).at(1).at(0).to_boolean());
}

TEST(Array, array_of_single0_string) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[\"foo\"]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.at(0).is_string());
  EXPECT_EQ(document.at(0).to_string(), "foo");
}

TEST(Array, comma_within_string_element) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[\"foo,bar\"]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.at(0).is_string());
  EXPECT_EQ(document.at(0).to_string(), "foo,bar");
}

TEST(Array, booleanarray_within_string_element) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[\"[false,true]\"]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.at(0).is_string());
  EXPECT_EQ(document.at(0).to_string(), "[false,true]");
}

TEST(Array, escaped_quote_within_string_element) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[\"foo\\\"bar\"]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.at(0).is_string());
  EXPECT_EQ(document.at(0).to_string(), "foo\"bar");
}

TEST(Array, single_positive_integer_element) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[4]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.at(0).is_integer());
  EXPECT_EQ(document.at(0).to_integer(), 4);
}

TEST(Array, single_negative_integer_element) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[-4]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.at(0).is_integer());
  EXPECT_EQ(document.at(0).to_integer(), -4);
}

TEST(Array, single_positive_real_number_element) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[4.3]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.at(0).is_real());
  EXPECT_EQ(document.at(0).to_real(), 4.3);
}

TEST(Array, single_negative_real_number_element) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[-4.3]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.at(0).is_real());
  EXPECT_EQ(document.at(0).to_real(), -4.3);
}

TEST(Array, single_exponential_number_element) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[3e2]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.at(0).is_real());
  EXPECT_EQ(document.at(0).to_real(), 300.0);
}

TEST(Array, single_empty_object_element) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[{}]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.at(0).is_object());
  EXPECT_EQ(document.at(0).size(), 0);
}

TEST(Array, single_object_element_with_one_simple_key) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[{\"foo\":1}]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.at(0).is_object());
  EXPECT_EQ(document.at(0).size(), 1);
  EXPECT_TRUE(document.at(0).at("foo").is_integer());
  EXPECT_EQ(document.at(0).at("foo").to_integer(), 1);
}

TEST(Array, single_object_element_with_two_simple_keys) {
  sourcemeta::jsontoolkit::JSON<std::string> document{
      "[{\"foo\":1,\"bar\":2}]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.at(0).is_object());
  EXPECT_EQ(document.at(0).size(), 2);
  EXPECT_TRUE(document.at(0).at("foo").is_integer());
  EXPECT_EQ(document.at(0).at("foo").to_integer(), 1);
  EXPECT_TRUE(document.at(0).at("bar").is_integer());
  EXPECT_EQ(document.at(0).at("bar").to_integer(), 2);
}

TEST(Array, equality_with_padding) {
  sourcemeta::jsontoolkit::JSON<std::string> left{"[1,2,3]"};
  left.parse();
  sourcemeta::jsontoolkit::JSON<std::string> right{"   [ 1  , 2,  3 ]"};
  right.parse();
  sourcemeta::jsontoolkit::JSON<std::string> extra{" [1,2,2]"};
  extra.parse();
  EXPECT_EQ(left, right);
  EXPECT_FALSE(left == extra);
  EXPECT_FALSE(right == extra);
}

TEST(Array, stringify_scalars_no_space) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[ 1, 2, 3 ]"};
  std::ostringstream stream;
  stream << document;
  EXPECT_EQ(stream.str(), "[1,2,3]");
  std::ostringstream cstream;
  cstream << std::as_const(document);
  EXPECT_EQ(cstream.str(), "[1,2,3]");
}

TEST(Array, stringify_scalars_space_pretty) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[ 1, 2, 3 ]"};
  std::ostringstream stream;
  stream << document.pretty();
  EXPECT_EQ(stream.str(), "[\n  1,\n  2,\n  3\n]");
  std::ostringstream cstream;
  cstream << std::as_const(document).pretty();
  EXPECT_EQ(cstream.str(), "[\n  1,\n  2,\n  3\n]");
}

TEST(Array, stringify_array_pretty) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[ 1, [2,3], 4 ]"};
  std::ostringstream stream;
  stream << document.pretty();
  EXPECT_EQ(stream.str(), "[\n  1,\n  [\n    2,\n    3\n  ],\n  4\n]");
  std::ostringstream cstream;
  cstream << std::as_const(document).pretty();
  EXPECT_EQ(cstream.str(), "[\n  1,\n  [\n    2,\n    3\n  ],\n  4\n]");
}

TEST(Array, stringify_object_pretty) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[ { \"foo\": 1 } ]"};
  std::ostringstream stream;
  stream << document.pretty();
  EXPECT_EQ(stream.str(), "[\n  {\n    \"foo\": 1\n  }\n]");
  std::ostringstream cstream;
  cstream << std::as_const(document).pretty();
  EXPECT_EQ(cstream.str(), "[\n  {\n    \"foo\": 1\n  }\n]");
}

TEST(Array, contains_string_key_true_unparsed) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[ \"foo\", \"bar\" ]"};
  sourcemeta::jsontoolkit::JSON<std::string> element{"\"bar\""};
  element.parse();
  EXPECT_TRUE(document.contains(element));
}

TEST(Array, contains_string_key_true_parsed) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[ \"foo\", \"bar\" ]"};
  document.parse();
  sourcemeta::jsontoolkit::JSON<std::string> element{"\"bar\""};
  element.parse();
  EXPECT_TRUE(document.contains(element));
}

TEST(Array, contains_string_key_true_const) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[ \"foo\", \"bar\" ]"};
  document.parse();
  sourcemeta::jsontoolkit::JSON<std::string> element{"\"bar\""};
  element.parse();
  EXPECT_TRUE(std::as_const(document).contains(element));
}

TEST(Array, contains_string_key_false_unparsed) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[ \"foo\", \"bar\" ]"};
  sourcemeta::jsontoolkit::JSON<std::string> element{"\"baz\""};
  element.parse();
  EXPECT_FALSE(document.contains(element));
}

TEST(Array, contains_string_key_false_parsed) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[ \"foo\", \"bar\" ]"};
  document.parse();
  sourcemeta::jsontoolkit::JSON<std::string> element{"\"baz\""};
  element.parse();
  EXPECT_FALSE(document.contains(element));
}

TEST(Array, contains_string_key_false_const) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[ \"foo\", \"bar\" ]"};
  document.parse();
  sourcemeta::jsontoolkit::JSON<std::string> element{"\"baz\""};
  element.parse();
  EXPECT_FALSE(std::as_const(document).contains(element));
}
