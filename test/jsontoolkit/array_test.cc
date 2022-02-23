#include <gtest/gtest.h>
#include <jsontoolkit/json.h>
#include <stdexcept> // std::domain_error

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
  EXPECT_EQ(document.at(0).to_boolean(), true);
}

TEST(Array, single_element_with_inner_space) {
  sourcemeta::jsontoolkit::JSON document{"[   true    ]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_EQ(document.at(0).to_boolean(), true);
}

TEST(Array, two_elements_with_spacing) {
  sourcemeta::jsontoolkit::JSON document{"[   true  ,   false   ]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 2);
  EXPECT_EQ(document.at(0).to_boolean(), true);
  EXPECT_EQ(document.at(1).to_boolean(), false);
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
  EXPECT_TRUE(document.at(0).is_array());
  EXPECT_TRUE(document.at(1).is_boolean());
  EXPECT_EQ(document.at(0).to_array()->size(), 1);
  EXPECT_TRUE(document.at(0).to_array()->at(0).is_boolean());
  EXPECT_TRUE(document.at(0).to_array()->at(0).to_boolean());
  EXPECT_FALSE(document.at(1).to_boolean());
}

TEST(Array, one_level_nested_array_with_padding) {
  sourcemeta::jsontoolkit::JSON document{"  [ [  true ]  ,  false  ]   "};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document.at(0).is_array());
  EXPECT_TRUE(document.at(1).is_boolean());
  EXPECT_EQ(document.at(0).to_array()->size(), 1);
  EXPECT_TRUE(document.at(0).to_array()->at(0).is_boolean());
  EXPECT_TRUE(document.at(0).to_array()->at(0).to_boolean());
  EXPECT_FALSE(document.at(1).to_boolean());
}

TEST(Array, two_levels_nested_array) {
  sourcemeta::jsontoolkit::JSON document{"[true,[false,[true]]]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document.at(0).is_boolean());
  EXPECT_TRUE(document.at(0).to_boolean());
  EXPECT_TRUE(document.at(1).is_array());
  EXPECT_EQ(document.at(1).to_array()->size(), 2);
  EXPECT_TRUE(document.at(1).to_array()->at(0).is_boolean());
  EXPECT_FALSE(document.at(1).to_array()->at(0).to_boolean());
  EXPECT_TRUE(document.at(1).to_array()->at(1).is_array());
  EXPECT_EQ(document.at(1).to_array()->at(1).size(), 1);
  EXPECT_TRUE(document.at(1).to_array()->at(1).to_array()->at(0).is_boolean());
  EXPECT_TRUE(document.at(1).to_array()->at(1).to_array()->at(0).to_boolean());
}

TEST(Array, two_levels_nested_array_with_padding) {
  sourcemeta::jsontoolkit::JSON document{
      "  [  true , [  false  , [ true ]  ]  ] "};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document.at(0).is_boolean());
  EXPECT_TRUE(document.at(0).to_boolean());
  EXPECT_TRUE(document.at(1).is_array());
  EXPECT_EQ(document.at(1).to_array()->size(), 2);
  EXPECT_TRUE(document.at(1).to_array()->at(0).is_boolean());
  EXPECT_FALSE(document.at(1).to_array()->at(0).to_boolean());
  EXPECT_TRUE(document.at(1).to_array()->at(1).is_array());
  EXPECT_EQ(document.at(1).to_array()->at(1).size(), 1);
  EXPECT_TRUE(document.at(1).to_array()->at(1).to_array()->at(0).is_boolean());
  EXPECT_TRUE(document.at(1).to_array()->at(1).to_array()->at(0).to_boolean());
}

TEST(Array, array_of_single_string) {
  sourcemeta::jsontoolkit::JSON document{"[\"foo\"]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.at(0).is_string());
  EXPECT_EQ(document.at(0).to_string(), "foo");
}

TEST(Array, comma_within_string_element) {
  sourcemeta::jsontoolkit::JSON document{"[\"foo,bar\"]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.at(0).is_string());
  EXPECT_EQ(document.at(0).to_string(), "foo,bar");
}

TEST(Array, booleanarray_within_string_element) {
  sourcemeta::jsontoolkit::JSON document{"[\"[false,true]\"]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.at(0).is_string());
  EXPECT_EQ(document.at(0).to_string(), "[false,true]");
}

TEST(Array, escaped_quote_within_string_element) {
  sourcemeta::jsontoolkit::JSON document{"[\"foo\\\"bar\"]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.at(0).is_string());
  EXPECT_EQ(document.at(0).to_string(), "foo\"bar");
}
