#include <gtest/gtest.h>
#include <jsontoolkit/json.h>
#include <stdexcept> // std::domain_error
#include <utility>   // std::as_const

TEST(Array, empty_array_string) {
  sourcemeta::jsontoolkit::JSON document{"[]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 0);
}

TEST(Array, empty_array_with_inner_space) {
  sourcemeta::jsontoolkit::JSON document{"[        ]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 0);
}

TEST(Array, empty_array_incomplete_right) {
  sourcemeta::jsontoolkit::JSON document{"["};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Array, empty_array_incomplete_right_with_inner_space) {
  sourcemeta::jsontoolkit::JSON document{"[  "};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Array, empty_with_comma) {
  sourcemeta::jsontoolkit::JSON document{"[,]"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Array, empty_with_comma_and_no_right_bracket) {
  sourcemeta::jsontoolkit::JSON document{"[,"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Array, empty_with_comma_and_spacing) {
  sourcemeta::jsontoolkit::JSON document{"[   ,   ]"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Array, parse_deep_success) {
  sourcemeta::jsontoolkit::JSON document{"[true]"};
  document.parse();
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_EQ(document.to_boolean(0), true);
}

TEST(Array, parse_deep_failure) {
  sourcemeta::jsontoolkit::JSON document{"[true"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(Array, parse_deep_failure_in_item) {
  sourcemeta::jsontoolkit::JSON document{"[tru]"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(Array, parse_is_lazy) {
  sourcemeta::jsontoolkit::JSON document{"[x,x]"};
  // Would throw otherwise
  EXPECT_EQ(document.size(), 2);
}

TEST(Array, array_without_comma_after_element) {
  sourcemeta::jsontoolkit::JSON document{"[1[2]]"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(Array, unclosed_string_element) {
  sourcemeta::jsontoolkit::JSON document{"[\"foo]"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(Array, single_element) {
  sourcemeta::jsontoolkit::JSON document{"[true]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_EQ(document.to_boolean(0), true);
}

TEST(Array, single_element_with_inner_space) {
  sourcemeta::jsontoolkit::JSON document{"[   true    ]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_EQ(document.to_boolean(0), true);
}

TEST(Array, two_elements_with_spacing) {
  sourcemeta::jsontoolkit::JSON document{"[   true  ,   false   ]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 2);
  EXPECT_EQ(document.to_boolean(0), true);
  EXPECT_EQ(document.to_boolean(1), false);
}

TEST(Array, single_element_trailing_comma) {
  sourcemeta::jsontoolkit::JSON document{"[true,]"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Array, single_element_trailing_commas) {
  sourcemeta::jsontoolkit::JSON document{"[true,,,]"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Array, single_element_middle_comma) {
  sourcemeta::jsontoolkit::JSON document{"[true,,true]"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Array, single_element_leading_comma) {
  sourcemeta::jsontoolkit::JSON document{"[,true]"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Array, single_element_leading_commas) {
  sourcemeta::jsontoolkit::JSON document{"[,,,true]"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Array, concat_array) {
  sourcemeta::jsontoolkit::JSON document{"[true][false]"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Array, concat_array_middle_comma) {
  sourcemeta::jsontoolkit::JSON document{"[true],[false]"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Array, concat_array_middle_unbalanced_left) {
  sourcemeta::jsontoolkit::JSON document{"[true],false]"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Array, concat_array_middle_unbalanced_right) {
  sourcemeta::jsontoolkit::JSON document{"[true,[false]"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Array, one_level_nested_array) {
  sourcemeta::jsontoolkit::JSON document{"[[true],false]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document.is_array(0));
  EXPECT_TRUE(document.is_boolean(1));
  EXPECT_EQ(document.size(0), 1);
  EXPECT_TRUE(document.at(0).is_boolean(0));
  EXPECT_TRUE(document.at(0).to_boolean(0));
  EXPECT_FALSE(document.to_boolean(1));
}

TEST(Array, one_level_nested_array_with_padding) {
  sourcemeta::jsontoolkit::JSON document{"  [ [  true ]  ,  false  ]   "};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document.is_array(0));
  EXPECT_TRUE(document.is_boolean(1));
  EXPECT_EQ(document.size(0), 1);
  EXPECT_TRUE(document.at(0).is_boolean(0));
  EXPECT_TRUE(document.at(0).to_boolean(0));
  EXPECT_FALSE(document.to_boolean(1));
}

TEST(Array, two_levels_nested_array) {
  sourcemeta::jsontoolkit::JSON document{"[true,[false,[true]]]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document.is_boolean(0));
  EXPECT_TRUE(document.to_boolean(0));
  EXPECT_TRUE(document.is_array(1));
  EXPECT_EQ(document.size(1), 2);
  EXPECT_TRUE(document.at(1).is_boolean(0));
  EXPECT_FALSE(document.at(1).to_boolean(0));
  EXPECT_TRUE(document.at(1).is_array(1));
  EXPECT_EQ(document.at(1).size(1), 1);
  EXPECT_TRUE(document.at(1).at(1).is_boolean(0));
  EXPECT_TRUE(document.at(1).at(1).to_boolean(0));
}

TEST(Array, two_levels_nested_array_clear) {
  sourcemeta::jsontoolkit::JSON document{"[true,[false,[true]]]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 2);
  document.clear();
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 0);
}

TEST(Array, two_levels_nested_array_clear_non_parsed) {
  sourcemeta::jsontoolkit::JSON document{"[true,[false,[true]]]"};
  document.clear();
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 0);
}

TEST(Array, two_levels_nested_array_with_padding) {
  sourcemeta::jsontoolkit::JSON document{
      "  [  true , [  false  , [ true ]  ]  ] "};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document.is_boolean(0));
  EXPECT_TRUE(document.to_boolean(0));
  EXPECT_TRUE(document.is_array(1));
  EXPECT_EQ(document.size(1), 2);
  EXPECT_TRUE(document.at(1).is_boolean(0));
  EXPECT_FALSE(document.at(1).to_boolean(0));
  EXPECT_TRUE(document.at(1).is_array(1));
  EXPECT_EQ(document.at(1).size(1), 1);
  EXPECT_TRUE(document.at(1).at(1).is_boolean(0));
  EXPECT_TRUE(document.at(1).at(1).to_boolean(0));
}

TEST(Array, array_of_single_string) {
  sourcemeta::jsontoolkit::JSON document{"[\"foo\"]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.is_string(0));
  EXPECT_EQ(document.to_string(0), "foo");
}

TEST(Array, comma_within_string_element) {
  sourcemeta::jsontoolkit::JSON document{"[\"foo,bar\"]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.is_string(0));
  EXPECT_EQ(document.to_string(0), "foo,bar");
}

TEST(Array, booleanarray_within_string_element) {
  sourcemeta::jsontoolkit::JSON document{"[\"[false,true]\"]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.is_string(0));
  EXPECT_EQ(document.to_string(0), "[false,true]");
}

TEST(Array, escaped_quote_within_string_element) {
  sourcemeta::jsontoolkit::JSON document{"[\"foo\\\"bar\"]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.is_string(0));
  EXPECT_EQ(document.to_string(0), "foo\"bar");
}

TEST(Array, single_positive_integer_element) {
  sourcemeta::jsontoolkit::JSON document{"[4]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.is_integer(0));
  EXPECT_EQ(document.to_integer(0), 4);
}

TEST(Array, single_negative_integer_element) {
  sourcemeta::jsontoolkit::JSON document{"[-4]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.is_integer(0));
  EXPECT_EQ(document.to_integer(0), -4);
}

TEST(Array, single_positive_real_number_element) {
  sourcemeta::jsontoolkit::JSON document{"[4.3]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.is_real(0));
  EXPECT_EQ(document.to_real(0), 4.3);
}

TEST(Array, single_negative_real_number_element) {
  sourcemeta::jsontoolkit::JSON document{"[-4.3]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.is_real(0));
  EXPECT_EQ(document.to_real(0), -4.3);
}

TEST(Array, single_exponential_number_element) {
  sourcemeta::jsontoolkit::JSON document{"[3e2]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.is_real(0));
  EXPECT_EQ(document.to_real(0), 300.0);
}

TEST(Array, single_empty_object_element) {
  sourcemeta::jsontoolkit::JSON document{"[{}]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.is_object(0));
  EXPECT_EQ(document.size(0), 0);
}

TEST(Array, single_object_element_with_one_simple_key) {
  sourcemeta::jsontoolkit::JSON document{"[{\"foo\":1}]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.is_object(0));
  EXPECT_EQ(document.size(0), 1);
  EXPECT_TRUE(document.at(0).is_integer("foo"));
  EXPECT_EQ(document.at(0).to_integer("foo"), 1);
}

TEST(Array, single_object_element_with_two_simple_keys) {
  sourcemeta::jsontoolkit::JSON document{"[{\"foo\":1,\"bar\":2}]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.is_object(0));
  EXPECT_EQ(document.size(0), 2);
  EXPECT_TRUE(document.at(0).is_integer("foo"));
  EXPECT_EQ(document.at(0).to_integer("foo"), 1);
  EXPECT_TRUE(document.at(0).is_integer("bar"));
  EXPECT_EQ(document.at(0).to_integer("bar"), 2);
}

TEST(Array, equality_with_padding) {
  sourcemeta::jsontoolkit::JSON left{"[1,2,3]"};
  left.parse();
  sourcemeta::jsontoolkit::JSON right{"   [ 1  , 2,  3 ]"};
  right.parse();
  sourcemeta::jsontoolkit::JSON extra{" [1,2,2]"};
  extra.parse();
  EXPECT_EQ(left, right);
  EXPECT_FALSE(left == extra);
  EXPECT_FALSE(right == extra);
}

TEST(Array, stringify_scalars_no_space) {
  sourcemeta::jsontoolkit::JSON document{"[ 1, 2, 3 ]"};
  EXPECT_EQ(document.stringify(), "[1,2,3]");
  EXPECT_EQ(std::as_const(document).stringify(), "[1,2,3]");
}

TEST(Array, stringify_scalars_space_pretty) {
  sourcemeta::jsontoolkit::JSON document{"[ 1, 2, 3 ]"};
  EXPECT_EQ(document.stringify(true), "[\n  1,\n  2,\n  3\n]");
  EXPECT_EQ(std::as_const(document).stringify(true), "[\n  1,\n  2,\n  3\n]");
}

TEST(Array, stringify_array_pretty) {
  sourcemeta::jsontoolkit::JSON document{"[ 1, [2,3], 4 ]"};
  EXPECT_EQ(document.stringify(true),
            "[\n  1,\n  [\n    2,\n    3\n  ],\n  4\n]");
  EXPECT_EQ(std::as_const(document).stringify(true),
            "[\n  1,\n  [\n    2,\n    3\n  ],\n  4\n]");
}

TEST(Array, stringify_object_pretty) {
  sourcemeta::jsontoolkit::JSON document{"[ { \"foo\": 1 } ]"};
  EXPECT_EQ(document.stringify(true), "[\n  {\n    \"foo\": 1\n  }\n]");
  EXPECT_EQ(std::as_const(document).stringify(true),
            "[\n  {\n    \"foo\": 1\n  }\n]");
}

TEST(Array, contains_string_key_true_unparsed) {
  sourcemeta::jsontoolkit::JSON document{"[ \"foo\", \"bar\" ]"};
  EXPECT_TRUE(document.contains("bar"));
}

TEST(Array, contains_string_key_true_parsed) {
  sourcemeta::jsontoolkit::JSON document{"[ \"foo\", \"bar\" ]"};
  document.parse();
  EXPECT_TRUE(document.contains("bar"));
}

TEST(Array, contains_string_key_true_const) {
  sourcemeta::jsontoolkit::JSON document{"[ \"foo\", \"bar\" ]"};
  document.parse();
  EXPECT_TRUE(std::as_const(document).contains("bar"));
}

TEST(Array, contains_string_key_false_unparsed) {
  sourcemeta::jsontoolkit::JSON document{"[ \"foo\", \"bar\" ]"};
  EXPECT_FALSE(document.contains("baz"));
}

TEST(Array, contains_string_key_false_parsed) {
  sourcemeta::jsontoolkit::JSON document{"[ \"foo\", \"bar\" ]"};
  document.parse();
  EXPECT_FALSE(document.contains("baz"));
}

TEST(Array, contains_string_key_false_const) {
  sourcemeta::jsontoolkit::JSON document{"[ \"foo\", \"bar\" ]"};
  document.parse();
  EXPECT_FALSE(std::as_const(document).contains("baz"));
}
