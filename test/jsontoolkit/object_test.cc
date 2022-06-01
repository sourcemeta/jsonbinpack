#include <algorithm> // std::all_of
#include <gtest/gtest.h>
#include <jsontoolkit/json.h>
#include <map>     // std::map
#include <utility> // std::move

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

TEST(Object, blank_object_string_empty) {
  sourcemeta::jsontoolkit::JSON document{"{    }"};
  EXPECT_TRUE(document.is_object());
  EXPECT_TRUE(document.empty());
}

TEST(Object, non_blank_object_string_not_empty) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":1}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_FALSE(document.empty());
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
  EXPECT_TRUE(document.is_boolean("foo"));
  EXPECT_TRUE(document.to_boolean("foo"));
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
  EXPECT_TRUE(document.is_boolean("foo"));
  EXPECT_TRUE(document.to_boolean("foo"));
}

TEST(Object, minified_one_false_boolean_element) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":false}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.is_boolean("foo"));
  EXPECT_FALSE(document.to_boolean("foo"));
}

TEST(Object, minified_two_boolean_values) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":true,\"bar\":false}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.contains("bar"));
  EXPECT_TRUE(document.is_boolean("foo"));
  EXPECT_TRUE(document.to_boolean("foo"));
  EXPECT_TRUE(document.is_boolean("bar"));
  EXPECT_FALSE(document.to_boolean("bar"));
}

TEST(Object, must_delete_one_existent_key) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":true,\"bar\":false}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.contains("bar"));
  document.erase("foo");
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
  document.erase("xxx");
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.contains("bar"));
}

TEST(Object, minified_one_array_element) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":[true,false]}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.is_array("foo"));
  EXPECT_EQ(document.size("foo"), 2);
  EXPECT_TRUE(document.at("foo").is_boolean(0));
  EXPECT_TRUE(document.at("foo").is_boolean(1));
  EXPECT_TRUE(document.at("foo").to_boolean(0));
  EXPECT_FALSE(document.at("foo").to_boolean(1));
}

TEST(Object, string_value_with_comma) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":\"bar,baz\"}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.is_string("foo"));
  EXPECT_EQ(document.at("foo"), "bar,baz");
}

TEST(Object, string_value_with_escaped_quote) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":\"bar\\\"baz\"}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.is_string("foo"));
  EXPECT_EQ(document.at("foo"), "bar\"baz");
}

TEST(Object, empty_string_key) {
  sourcemeta::jsontoolkit::JSON document{"{\"\":\"foo\"}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains(""));
  EXPECT_TRUE(document.is_string(""));
  EXPECT_EQ(document.at(""), "foo");
}

TEST(Object, string_key_with_comma) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo,bar\":\"baz\"}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo,bar"));
  EXPECT_TRUE(document.is_string("foo,bar"));
  EXPECT_EQ(document.at("foo,bar"), "baz");
}

TEST(Object, string_key_with_space) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo bar\":\"baz\"}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo bar"));
  EXPECT_TRUE(document.is_string("foo bar"));
  EXPECT_EQ(document.at("foo bar"), "baz");
}

TEST(Object, string_value_with_stringified_object) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":\"{\\\"x\\\":1}\"}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.is_string("foo"));
  EXPECT_EQ(document.at("foo"), "{\"x\":1}");
}

TEST(Object, one_true_boolean_element_with_space) {
  sourcemeta::jsontoolkit::JSON document{"    {   \"foo\"   :   true  }    "};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.is_boolean("foo"));
  EXPECT_TRUE(document.to_boolean("foo"));
}

TEST(Object, two_boolean_values_with_space) {
  sourcemeta::jsontoolkit::JSON document{
      "{   \"foo\"  :   true    ,     \"bar\"   :   false}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.contains("bar"));
  EXPECT_TRUE(document.is_boolean("foo"));
  EXPECT_TRUE(document.to_boolean("foo"));
  EXPECT_TRUE(document.is_boolean("bar"));
  EXPECT_FALSE(document.to_boolean("bar"));
}

TEST(Object, one_array_element_with_space) {
  sourcemeta::jsontoolkit::JSON document{
      "{   \"foo\"   :  [  true  ,  false   ]   }"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.is_array("foo"));
  EXPECT_EQ(document.size("foo"), 2);
  EXPECT_TRUE(document.at("foo").is_boolean(0));
  EXPECT_TRUE(document.at("foo").is_boolean(1));
  EXPECT_TRUE(document.at("foo").to_boolean(0));
  EXPECT_FALSE(document.at("foo").to_boolean(1));
}

TEST(Object, nested_object_clear) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":{\"bar\":true}}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  document.clear();
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 0);
}

TEST(Object, nested_object_clear_non_parsed) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":{\"bar\":true}}"};
  document.clear();
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 0);
}

TEST(Object, minified_nested_object) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":{\"bar\":true}}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.is_object("foo"));
  EXPECT_EQ(document.size("foo"), 1);
  EXPECT_TRUE(document.at("foo").contains("bar"));
}

TEST(Object, empty_nested_object_with_new_line_before_end) {
  sourcemeta::jsontoolkit::JSON document("{\"x\":{}\n}");
  document.parse();
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("x"));
  EXPECT_TRUE(document.is_object("x"));
  EXPECT_EQ(document.size("x"), 0);
}

TEST(Object, equality_with_padding) {
  sourcemeta::jsontoolkit::JSON left{"{\"foo\":1}"};
  left.parse();
  sourcemeta::jsontoolkit::JSON right{"  { \"foo\"   : 1 } "};
  right.parse();
  sourcemeta::jsontoolkit::JSON extra{" { \"fo\":1 }"};
  extra.parse();
  EXPECT_EQ(left, right);
  EXPECT_FALSE(left == extra);
  EXPECT_FALSE(right == extra);
}

TEST(Object, stringify_single_scalar_no_space) {
  sourcemeta::jsontoolkit::JSON document{"{ \"foo\": 1 }"};
  const std::string result{document.stringify()};
  EXPECT_EQ(result, "{\"foo\":1}");
}

TEST(Object, stringify_scalars_no_space) {
  sourcemeta::jsontoolkit::JSON document{"{ \"foo\": 1, \"bar\": true }"};
  const std::string result{document.stringify()};
  // Because order is irrelevant
  const bool matches = result == "{\"foo\":1,\"bar\":true}" ||
                       result == "{\"bar\":true,\"foo\":1}";
  EXPECT_TRUE(matches);
}

TEST(Object, stringify_single_scalar_pretty) {
  sourcemeta::jsontoolkit::JSON document{"{ \"foo\": 1 }"};
  const std::string result{document.stringify(true)};
  EXPECT_EQ(result, "{\n  \"foo\": 1\n}");
}

TEST(Object, stringify_scalars_pretty) {
  sourcemeta::jsontoolkit::JSON document{"{ \"foo\": 1, \"bar\": true }"};
  const std::string result{document.stringify(true)};
  // Because order is irrelevant
  const bool matches = result == "{\n  \"foo\": 1,\n  \"bar\": true\n}" ||
                       result == "{\n  \"bar\": true,\n  \"foo\": 1\n}";
  EXPECT_TRUE(matches);
}

TEST(Object, stringify_single_array_no_space) {
  sourcemeta::jsontoolkit::JSON document{"{ \"foo\": [1,2] }"};
  const std::string result{document.stringify()};
  EXPECT_EQ(result, "{\"foo\":[1,2]}");
}

TEST(Object, stringify_single_array_pretty) {
  sourcemeta::jsontoolkit::JSON document{"{ \"foo\": [1,2] }"};
  const std::string result{document.stringify(true)};
  EXPECT_EQ(result, "{\n  \"foo\": [\n    1,\n    2\n  ]\n}");
}

TEST(Object, stringify_single_object_pretty) {
  sourcemeta::jsontoolkit::JSON document{"{ \"foo\": {\"bar\":1} }"};
  const std::string result{document.stringify(true)};
  EXPECT_EQ(result, "{\n  \"foo\": {\n    \"bar\": 1\n  }\n}");
}

TEST(Object, const_all_of_true) {
  sourcemeta::jsontoolkit::JSON document{"{ \"foo\": 1, \"bar\": 2 }"};
  document.parse();
  const bool result =
      std::all_of(document.to_object().cbegin(), document.to_object().cend(),
                  [](auto pair) { return pair.second.is_integer(); });
  EXPECT_TRUE(result);
}

TEST(Object, const_all_of_false) {
  sourcemeta::jsontoolkit::JSON document{"{ \"foo\": 1, \"bar\": \"2\" }"};
  document.parse();
  const bool result =
      std::all_of(document.to_object().cbegin(), document.to_object().cend(),
                  [](auto pair) { return pair.second.is_integer(); });
  EXPECT_FALSE(result);
}

TEST(Object, const_all_of_on_const_instance) {
  sourcemeta::jsontoolkit::JSON source{"{ \"foo\": 1, \"bar\": 2 }"};
  source.parse();
  const sourcemeta::jsontoolkit::JSON document{std::move(source)};
  const bool result =
      std::all_of(document.to_object().cbegin(), document.to_object().cend(),
                  [](auto pair) { return pair.second.is_integer(); });
  EXPECT_TRUE(result);
}

TEST(Object, key_copy_assignment_same_type_parsed) {
  sourcemeta::jsontoolkit::JSON document{"{ \"foo\": \"bar\" }"};
  document.parse();
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.is_string("foo"));
  EXPECT_EQ(document.at("foo"), "bar");

  sourcemeta::jsontoolkit::JSON value{"\"baz\""};
  value.parse();
  document.assign("foo", value);

  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.is_string("foo"));
  EXPECT_EQ(document.at("foo"), "baz");
}

TEST(Object, key_move_assignment_same_type_parsed) {
  sourcemeta::jsontoolkit::JSON document{"{ \"foo\": \"bar\" }"};
  document.parse();
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.is_string("foo"));
  EXPECT_EQ(document.at("foo"), "bar");

  sourcemeta::jsontoolkit::JSON value{"\"baz\""};
  value.parse();
  document.assign("foo", std::move(value));

  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.is_string("foo"));
  EXPECT_EQ(document.at("foo"), "baz");
}

TEST(Object, key_copy_assignment_different_type_parsed) {
  sourcemeta::jsontoolkit::JSON document{"{ \"foo\": \"bar\" }"};
  document.parse();
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.is_string("foo"));
  EXPECT_EQ(document.at("foo"), "bar");

  sourcemeta::jsontoolkit::JSON value{"1"};
  value.parse();
  document.assign("foo", value);

  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.is_integer("foo"));
  EXPECT_EQ(document.at("foo"), static_cast<std::int64_t>(1));
}

TEST(Object, key_move_assignment_different_type_parsed) {
  sourcemeta::jsontoolkit::JSON document{"{ \"foo\": \"bar\" }"};
  document.parse();
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.is_string("foo"));
  EXPECT_EQ(document.at("foo"), "bar");

  sourcemeta::jsontoolkit::JSON value{"1"};
  value.parse();
  document.assign("foo", std::move(value));

  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.is_integer("foo"));
  EXPECT_EQ(document.at("foo"), static_cast<std::int64_t>(1));
}

TEST(Object, key_copy_assignment_same_type_unparsed) {
  sourcemeta::jsontoolkit::JSON document{"{ \"foo\": \"bar\" }"};
  document.parse();
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.is_string("foo"));
  EXPECT_EQ(document.at("foo"), "bar");

  sourcemeta::jsontoolkit::JSON value{"\"baz\""};
  document.assign("foo", value);

  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.is_string("foo"));
  EXPECT_EQ(document.at("foo"), "baz");
}

TEST(Object, key_move_assignment_same_type_unparsed) {
  sourcemeta::jsontoolkit::JSON document{"{ \"foo\": \"bar\" }"};
  document.parse();
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.is_string("foo"));
  EXPECT_EQ(document.at("foo"), "bar");

  sourcemeta::jsontoolkit::JSON value{"\"baz\""};
  document.assign("foo", std::move(value));

  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.is_string("foo"));
  EXPECT_EQ(document.at("foo"), "baz");
}

TEST(Object, new_key_copy_assignment) {
  sourcemeta::jsontoolkit::JSON document{"{ \"foo\": \"bar\" }"};
  document.parse();
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.is_string("foo"));
  EXPECT_EQ(document.at("foo"), "bar");

  sourcemeta::jsontoolkit::JSON new_value{"\"baz\""};
  document.assign("bar", new_value);

  EXPECT_EQ(document.size(), 2);

  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.is_string("foo"));
  EXPECT_EQ(document.at("foo"), "bar");

  EXPECT_TRUE(document.contains("bar"));
  EXPECT_TRUE(document.is_string("bar"));
  EXPECT_EQ(document.at("bar"), "baz");
}

TEST(Object, new_key_move_assignment) {
  sourcemeta::jsontoolkit::JSON document{"{ \"foo\": \"bar\" }"};
  document.parse();
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.is_string("foo"));
  EXPECT_EQ(document.at("foo"), "bar");

  sourcemeta::jsontoolkit::JSON new_value{"\"baz\""};
  document.assign("bar", std::move(new_value));

  EXPECT_EQ(document.size(), 2);

  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.is_string("foo"));
  EXPECT_EQ(document.at("foo"), "bar");

  EXPECT_TRUE(document.contains("bar"));
  EXPECT_TRUE(document.is_string("bar"));
  EXPECT_EQ(document.at("bar"), "baz");
}

TEST(Object, assign_literal_lvalue_string) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":1}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  const std::string value{"baz"};
  document.assign("bar", value);
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.contains("bar"));
  document.parse();
  EXPECT_EQ(document.at("foo"), static_cast<std::int64_t>(1));
  EXPECT_EQ(document.at("bar"), "baz");
}

TEST(Object, assign_literal_rvalue_string) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":1}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  document.assign("bar", std::string{"baz"});
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.contains("bar"));
  document.parse();
  EXPECT_EQ(document.at("foo"), static_cast<std::int64_t>(1));
  EXPECT_EQ(document.at("bar"), "baz");
}

TEST(Object, map_copy_constructor) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":1}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.is_integer("foo"));
  const std::map<std::string, sourcemeta::jsontoolkit::JSON> value{
      {"bar", static_cast<std::int64_t>(5)}};
  document.assign("xxx", value);
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.is_integer("foo"));
  EXPECT_TRUE(document.contains("xxx"));
  EXPECT_TRUE(document.is_object("xxx"));
  EXPECT_EQ(document.size("xxx"), 1);
  EXPECT_TRUE(document.at("xxx").contains("bar"));
  EXPECT_TRUE(document.at("xxx").is_integer("bar"));
  EXPECT_EQ(document.at("xxx").at("bar"), static_cast<std::int64_t>(5));
}

TEST(Object, map_move_constructor) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":1}"};
  EXPECT_TRUE(document.is_object());
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.is_integer("foo"));
  std::map<std::string, sourcemeta::jsontoolkit::JSON> value{
      {"bar", static_cast<std::int64_t>(5)}};
  document.assign("xxx", std::move(value));
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.is_integer("foo"));
  EXPECT_TRUE(document.contains("xxx"));
  EXPECT_TRUE(document.is_object("xxx"));
  EXPECT_EQ(document.size("xxx"), 1);
  EXPECT_TRUE(document.at("xxx").contains("bar"));
  EXPECT_TRUE(document.at("xxx").is_integer("bar"));
  EXPECT_EQ(document.at("xxx").at("bar"), static_cast<std::int64_t>(5));
}
