#include <gtest/gtest.h>
#include <jsontoolkit/json.h>

TEST(Object, empty_object_string) {
  sourcemeta::jsontoolkit::JSON document{"{}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 0);
}

TEST(Object, blank_object_string) {
  sourcemeta::jsontoolkit::JSON document{"{    }"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 0);
}

TEST(Object, empty_object_missing_left_curly) {
  sourcemeta::jsontoolkit::JSON document{"}"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Object, empty_object_missing_right_curly) {
  sourcemeta::jsontoolkit::JSON document{"{"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Object, integer_key) {
  sourcemeta::jsontoolkit::JSON document{"{1:false}"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Object, colon_but_no_key) {
  sourcemeta::jsontoolkit::JSON document{"{:false}"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Object, colon_but_no_key_with_space) {
  sourcemeta::jsontoolkit::JSON document{"{  :  false  }"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Object, colon_but_no_value) {
  sourcemeta::jsontoolkit::JSON document{"{\"x\":}"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Object, colon_but_no_value_with_space) {
  sourcemeta::jsontoolkit::JSON document{"{   \"x\"   :   }"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Object, missing_key_left_quote) {
  sourcemeta::jsontoolkit::JSON document{"{foo\":true}"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Object, missing_key_right_quote) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo:true}"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Object, missing_key_both_quotes) {
  sourcemeta::jsontoolkit::JSON document{"{foo:true}"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Object, missing_colon) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\" true}"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Object, multiple_colons) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\"::true}"};
  EXPECT_THROW(document.size(), std::domain_error);
}

TEST(Object, parse_deep_success) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":true}"};
  document.parse();
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document["foo"].is_boolean());
  EXPECT_TRUE(document["foo"].to_boolean());
}

TEST(Object, parse_deep_failure) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":true"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(Object, parse_deep_failure_member) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":tru}"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(Object, key_without_value) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\"}"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(Object, key_without_value_after_valid_key) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\": 1,\"bar\"}"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(Object, trailing_comma_after_element) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\": 1,\"bar\":0,}"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(Object, trailing_comma) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\": 1,}"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(Object, trailing_comma_with_spacing) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\": 1  ,   } "};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(Object, trailing_comma_with_left_spacing) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\": 1  ,}"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(Object, multiple_commas) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\": 1,,,,,}"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(Object, multiple_commas_with_spacing) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\": 1 ,  ,  , , }"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(Object, minified_one_true_boolean_element) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":true}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document["foo"].is_boolean());
  EXPECT_TRUE(document["foo"].to_boolean());
}

TEST(Object, minified_one_false_boolean_element) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":false}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document["foo"].is_boolean());
  EXPECT_FALSE(document["foo"].to_boolean());
}

TEST(Object, minified_two_boolean_values) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":true,\"bar\":false}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.contains("bar"));
  EXPECT_TRUE(document["foo"].is_boolean());
  EXPECT_TRUE(document["foo"].to_boolean());
  EXPECT_TRUE(document["bar"].is_boolean());
  EXPECT_FALSE(document["bar"].to_boolean());
}

TEST(Object, must_delete_one_existent_key) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":true,\"bar\":false}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.contains("bar"));
  const std::size_t count = document.erase("foo");
  EXPECT_EQ(count, 1);
  EXPECT_EQ(document.size(), 1);
  EXPECT_FALSE(document.contains("foo"));
  EXPECT_TRUE(document.contains("bar"));
}

TEST(Object, must_delete_one_non_existent_key) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":true,\"bar\":false}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.contains("bar"));
  const std::size_t count = document.erase("xxx");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.contains("bar"));
}

TEST(Object, minified_one_array_element) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":[true,false]}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document["foo"].is_array());
  EXPECT_EQ(document["foo"].size(), 2);
  EXPECT_TRUE(document["foo"][0].is_boolean());
  EXPECT_TRUE(document["foo"][1].is_boolean());
  EXPECT_TRUE(document["foo"][0].to_boolean());
  EXPECT_FALSE(document["foo"][1].to_boolean());
}

TEST(Object, string_value_with_comma) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":\"bar,baz\"}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document["foo"].is_string());
  EXPECT_EQ(document["foo"], "bar,baz");
}

TEST(Object, string_value_with_escaped_quote) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":\"bar\\\"baz\"}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document["foo"].is_string());
  EXPECT_EQ(document["foo"], "bar\"baz");
}

TEST(Object, empty_string_key) {
  sourcemeta::jsontoolkit::JSON document{"{\"\":\"foo\"}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains(""));
  EXPECT_TRUE(document[""].is_string());
  EXPECT_EQ(document[""], "foo");
}

TEST(Object, string_key_with_comma) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo,bar\":\"baz\"}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo,bar"));
  EXPECT_TRUE(document["foo,bar"].is_string());
  EXPECT_EQ(document["foo,bar"], "baz");
}

TEST(Object, string_key_with_space) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo bar\":\"baz\"}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo bar"));
  EXPECT_TRUE(document["foo bar"].is_string());
  EXPECT_EQ(document["foo bar"], "baz");
}

TEST(Object, string_value_with_stringified_object) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":\"{\\\"x\\\":1}\"}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document["foo"].is_string());
  EXPECT_EQ(document["foo"], "{\"x\":1}");
}

TEST(Object, one_true_boolean_element_with_space) {
  sourcemeta::jsontoolkit::JSON document{"    {   \"foo\"   :   true  }    "};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document["foo"].is_boolean());
  EXPECT_TRUE(document["foo"].to_boolean());
}

TEST(Object, two_boolean_values_with_space) {
  sourcemeta::jsontoolkit::JSON document{
      "{   \"foo\"  :   true    ,     \"bar\"   :   false}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.contains("bar"));
  EXPECT_TRUE(document["foo"].is_boolean());
  EXPECT_TRUE(document["foo"].to_boolean());
  EXPECT_TRUE(document["bar"].is_boolean());
  EXPECT_FALSE(document["bar"].to_boolean());
}

TEST(Object, one_array_element_with_space) {
  sourcemeta::jsontoolkit::JSON document{
      "{   \"foo\"   :  [  true  ,  false   ]   }"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document["foo"].is_array());
  EXPECT_EQ(document["foo"].size(), 2);
  EXPECT_TRUE(document["foo"][0].is_boolean());
  EXPECT_TRUE(document["foo"][1].is_boolean());
  EXPECT_TRUE(document["foo"][0].to_boolean());
  EXPECT_FALSE(document["foo"][1].to_boolean());
}

TEST(Object, minified_nested_object) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":{\"bar\":true}}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document["foo"].is_object());
  EXPECT_EQ(document["foo"].size(), 1);
  EXPECT_TRUE(document["foo"].contains("bar"));
}
