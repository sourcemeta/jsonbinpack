#include <gtest/gtest.h>
#include <jsontoolkit/json.h>
#include <stdexcept> // std::domain_error

TEST(Array, nothrow_move_constructible) {
  EXPECT_TRUE(std::is_nothrow_move_constructible<
              sourcemeta::jsontoolkit::Array>::value);
}

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

TEST(Array, single_element) {
  sourcemeta::jsontoolkit::JSON document{"[true]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_EQ(document[0].to_boolean(), true);
}

TEST(Array, single_element_with_inner_space) {
  sourcemeta::jsontoolkit::JSON document{"[   true    ]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_EQ(document[0].to_boolean(), true);
}

TEST(Array, two_elements_with_spacing) {
  sourcemeta::jsontoolkit::JSON document{"[   true  ,   false   ]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 2);
  EXPECT_EQ(document[0].to_boolean(), true);
  EXPECT_EQ(document[1].to_boolean(), false);
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
  EXPECT_TRUE(document[0].is_array());
  EXPECT_TRUE(document[1].is_boolean());
  EXPECT_EQ(document[0].to_array()->size(), 1);
  EXPECT_TRUE(document[0].to_array()->at(0).is_boolean());
  EXPECT_TRUE(document[0].to_array()->at(0).to_boolean());
  EXPECT_FALSE(document[1].to_boolean());
}

TEST(Array, one_level_nested_array_with_padding) {
  sourcemeta::jsontoolkit::JSON document{"  [ [  true ]  ,  false  ]   "};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document[0].is_array());
  EXPECT_TRUE(document[1].is_boolean());
  EXPECT_EQ(document[0].to_array()->size(), 1);
  EXPECT_TRUE(document[0].to_array()->at(0).is_boolean());
  EXPECT_TRUE(document[0].to_array()->at(0).to_boolean());
  EXPECT_FALSE(document[1].to_boolean());
}

TEST(Array, two_levels_nested_array) {
  sourcemeta::jsontoolkit::JSON document{"[true,[false,[true]]]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document[0].is_boolean());
  EXPECT_TRUE(document[0].to_boolean());
  EXPECT_TRUE(document[1].is_array());
  EXPECT_EQ(document[1].to_array()->size(), 2);
  EXPECT_TRUE(document[1].to_array()->at(0).is_boolean());
  EXPECT_FALSE(document[1].to_array()->at(0).to_boolean());
  EXPECT_TRUE(document[1].to_array()->at(1).is_array());
  EXPECT_EQ(document[1].to_array()->at(1).size(), 1);
  EXPECT_TRUE(document[1].to_array()->at(1).to_array()->at(0).is_boolean());
  EXPECT_TRUE(document[1].to_array()->at(1).to_array()->at(0).to_boolean());
}

TEST(Array, two_levels_nested_array_with_padding) {
  sourcemeta::jsontoolkit::JSON document{
      "  [  true , [  false  , [ true ]  ]  ] "};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document[0].is_boolean());
  EXPECT_TRUE(document[0].to_boolean());
  EXPECT_TRUE(document[1].is_array());
  EXPECT_EQ(document[1].to_array()->size(), 2);
  EXPECT_TRUE(document[1].to_array()->at(0).is_boolean());
  EXPECT_FALSE(document[1].to_array()->at(0).to_boolean());
  EXPECT_TRUE(document[1].to_array()->at(1).is_array());
  EXPECT_EQ(document[1].to_array()->at(1).size(), 1);
  EXPECT_TRUE(document[1].to_array()->at(1).to_array()->at(0).is_boolean());
  EXPECT_TRUE(document[1].to_array()->at(1).to_array()->at(0).to_boolean());
}

TEST(Array, array_of_single_string) {
  sourcemeta::jsontoolkit::JSON document{"[\"foo\"]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document[0].is_string());
  EXPECT_EQ(document[0].to_string(), "foo");
}

TEST(Array, comma_within_string_element) {
  sourcemeta::jsontoolkit::JSON document{"[\"foo,bar\"]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document[0].is_string());
  EXPECT_EQ(document[0].to_string(), "foo,bar");
}

TEST(Array, booleanarray_within_string_element) {
  sourcemeta::jsontoolkit::JSON document{"[\"[false,true]\"]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document[0].is_string());
  EXPECT_EQ(document[0].to_string(), "[false,true]");
}

TEST(Array, escaped_quote_within_string_element) {
  sourcemeta::jsontoolkit::JSON document{"[\"foo\\\"bar\"]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document[0].is_string());
  EXPECT_EQ(document[0].to_string(), "foo\"bar");
}

TEST(Array, single_positive_integer_element) {
  sourcemeta::jsontoolkit::JSON document{"[4]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document[0].is_integer());
  EXPECT_EQ(document[0].to_integer(), 4);
}

TEST(Array, single_negative_integer_element) {
  sourcemeta::jsontoolkit::JSON document{"[-4]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document[0].is_integer());
  EXPECT_EQ(document[0].to_integer(), -4);
}

TEST(Array, single_positive_real_number_element) {
  sourcemeta::jsontoolkit::JSON document{"[4.3]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document[0].is_real());
  EXPECT_EQ(document[0].to_real(), 4.3);
}

TEST(Array, single_negative_real_number_element) {
  sourcemeta::jsontoolkit::JSON document{"[-4.3]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document[0].is_real());
  EXPECT_EQ(document[0].to_real(), -4.3);
}

TEST(Array, single_exponential_number_element) {
  sourcemeta::jsontoolkit::JSON document{"[3e2]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document[0].is_real());
  EXPECT_EQ(document[0].to_real(), 300.0);
}

TEST(Array, single_empty_object_element) {
  sourcemeta::jsontoolkit::JSON document{"[{}]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document[0].is_object());
  EXPECT_EQ(document[0].size(), 0);
}

TEST(Array, single_object_element_with_one_simple_key) {
  sourcemeta::jsontoolkit::JSON document{"[{\"foo\":1}]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document[0].is_object());
  EXPECT_EQ(document[0].size(), 1);
  EXPECT_TRUE(document[0]["foo"].is_integer());
  EXPECT_EQ(document[0]["foo"].to_integer(), 1);
}

TEST(Array, single_object_element_with_two_simple_keys) {
  sourcemeta::jsontoolkit::JSON document{"[{\"foo\":1,\"bar\":2}]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document[0].is_object());
  EXPECT_EQ(document[0].size(), 2);
  EXPECT_TRUE(document[0]["foo"].is_integer());
  EXPECT_EQ(document[0]["foo"].to_integer(), 1);
  EXPECT_TRUE(document[0]["bar"].is_integer());
  EXPECT_EQ(document[0]["bar"].to_integer(), 2);
}
