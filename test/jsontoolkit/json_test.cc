#include <cstdint> // std::int64_t
#include <gtest/gtest.h>
#include <jsontoolkit/json.h>
#include <stdexcept> // std::domain_error
#include <type_traits> // std::is_nothrow_move_constructible, std::is_default_constructible
#include <utility> // std::as_const
#include <vector>  // std::vector

TEST(JSON, nothrow_move_constructible) {
  EXPECT_TRUE(
      std::is_nothrow_move_constructible<sourcemeta::jsontoolkit::JSON>::value);
}

TEST(JSON, default_constructible_is_invalid) {
  EXPECT_TRUE(
      std::is_default_constructible<sourcemeta::jsontoolkit::JSON>::value);
  sourcemeta::jsontoolkit::JSON document;
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(JSON, set_boolean) {
  sourcemeta::jsontoolkit::JSON document{false};
  EXPECT_TRUE(document.is_boolean());
  EXPECT_EQ(document, false);
  document = true;
  EXPECT_TRUE(document.is_boolean());
  EXPECT_EQ(document, true);
  document = false;
  EXPECT_TRUE(document.is_boolean());
  EXPECT_EQ(document, false);
}

TEST(JSON, bool_deep_parse) {
  sourcemeta::jsontoolkit::JSON document{"true"};
  document.parse();
  EXPECT_EQ(document, true);
}

TEST(JSON, bool_deep_parse_failure) {
  sourcemeta::jsontoolkit::JSON document{"tru"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(JSON, int_deep_parse) {
  sourcemeta::jsontoolkit::JSON document{"4"};
  document.parse();
  EXPECT_EQ(document, static_cast<std::int64_t>(4));
}

TEST(JSON, int_deep_parse_failure) {
  sourcemeta::jsontoolkit::JSON document{"32,2"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(JSON, real_deep_parse) {
  sourcemeta::jsontoolkit::JSON document{"3.14"};
  document.parse();
  EXPECT_EQ(document, 3.14);
}

TEST(JSON, real_deep_parse_failure) {
  sourcemeta::jsontoolkit::JSON document{"32.2.2"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(JSON, null_deep_parse) {
  sourcemeta::jsontoolkit::JSON document{"null"};
  document.parse();
  EXPECT_EQ(document, nullptr);
}

TEST(JSON, null_deep_parse_failure) {
  sourcemeta::jsontoolkit::JSON document{"nul"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(json, string_deep_parse) {
  sourcemeta::jsontoolkit::JSON document{"\"foo\""};
  document.parse();
  EXPECT_EQ(document, "foo");
}

TEST(JSON, string_deep_parse_failure) {
  sourcemeta::jsontoolkit::JSON document{"\"foo"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(JSON, array_deep_parse) {
  sourcemeta::jsontoolkit::JSON document{"[true,false,true]"};
  document.parse();
  EXPECT_EQ(document.size(), 3);
  EXPECT_EQ(std::as_const(document).size(), 3);
}

TEST(JSON, array_deep_parse_failure) {
  sourcemeta::jsontoolkit::JSON document{"[true,fals,true]"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(JSON, object_deep_parse) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":2}"};
  document.parse();
  EXPECT_EQ(document.size(), 1);
  EXPECT_EQ(std::as_const(document).size(), 1);
}

TEST(JSON, object_deep_parse_failure) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":tru}"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(JSON, not_bool_equality_string) {
  sourcemeta::jsontoolkit::JSON document{"\"foo\""};
  EXPECT_FALSE(document.is_boolean());
  EXPECT_FALSE(document == true);
}

TEST(JSON, not_bool_equality_int) {
  sourcemeta::jsontoolkit::JSON document{static_cast<std::int64_t>(6)};
  EXPECT_FALSE(document.is_boolean());
  EXPECT_FALSE(document == true);
}

TEST(JSON, at_boolean) {
  sourcemeta::jsontoolkit::JSON document{"[true,false,true]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 3);
  EXPECT_EQ(std::as_const(document).size(), 3);

  EXPECT_TRUE(document[0].is_boolean());
  EXPECT_TRUE(document[1].is_boolean());
  EXPECT_TRUE(document[2].is_boolean());

  EXPECT_EQ(document[0], true);
  EXPECT_EQ(document[1], false);
  EXPECT_EQ(document[2], true);
}

TEST(JSON, boolean_array_iterator) {
  sourcemeta::jsontoolkit::JSON value{"[true,false,false]"};
  std::vector<bool> result;

  for (sourcemeta::jsontoolkit::JSON &element : value.to_array()) {
    result.push_back(element.to_boolean());
  }

  EXPECT_EQ(result.size(), 3);
  EXPECT_TRUE(result.at(0));
  EXPECT_FALSE(result.at(1));
  EXPECT_FALSE(result.at(2));
}

TEST(JSON, boolean_array_reverse_iterator) {
  sourcemeta::jsontoolkit::JSON value{"[true,false,false]"};
  std::vector<bool> result;

  // TODO: Can we hide the Array type somehow?
  for (sourcemeta::jsontoolkit::Array::reverse_iterator iterator =
           value.to_array().rbegin();
       iterator != value.to_array().rend(); iterator++) {
    result.push_back(iterator->to_boolean());
  }

  EXPECT_EQ(result.size(), 3);
  EXPECT_FALSE(result.at(0));
  EXPECT_FALSE(result.at(1));
  EXPECT_TRUE(result.at(2));
}

TEST(JSON, array_padded_parse) {
  sourcemeta::jsontoolkit::JSON value{"  [true,false,false]  "};
  EXPECT_TRUE(value.is_array());
}

// https://datatracker.ietf.org/doc/html/rfc8259#section-13
TEST(JSON, rfc8259_example_1) {
  sourcemeta::jsontoolkit::JSON value{
      "{\n"
      "\"Image\": {\n"
      "\"Width\":  800,\n"
      "\"Height\": 600,\n"
      "\"Title\":  \"View from 15th Floor\",\n"
      "\"Thumbnail\": {\n"
      "\"Url\":    \"http://www.example.com/image/481989943\",\n"
      "\"Height\": 125,\n"
      "\"Width\":  100\n"
      "},\n"
      "\"Animated\" : false,\n"
      "\"IDs\": [116, 943, 234, 38793]\n"
      "}\n"
      "}"};

  // Top level object
  EXPECT_TRUE(value.is_object());
  EXPECT_EQ(value.size(), 1);
  EXPECT_TRUE(value.contains("Image"));

  // Image object
  EXPECT_TRUE(value["Image"].is_object());
  EXPECT_EQ(value["Image"].size(), 6);
  EXPECT_TRUE(value["Image"].contains("Width"));
  EXPECT_TRUE(value["Image"].contains("Height"));
  EXPECT_TRUE(value["Image"].contains("Title"));
  EXPECT_TRUE(value["Image"].contains("Thumbnail"));
  EXPECT_TRUE(value["Image"].contains("Animated"));
  EXPECT_TRUE(value["Image"].contains("IDs"));
  EXPECT_TRUE(value["Image"]["Width"].is_integer());
  EXPECT_TRUE(value["Image"]["Height"].is_integer());
  EXPECT_TRUE(value["Image"]["Title"].is_string());
  EXPECT_TRUE(value["Image"]["Thumbnail"].is_object());
  EXPECT_TRUE(value["Image"]["Animated"].is_boolean());
  EXPECT_TRUE(value["Image"]["IDs"].is_array());
  EXPECT_EQ(value["Image"]["Width"].to_integer(), 800);
  EXPECT_EQ(value["Image"]["Height"].to_integer(), 600);
  EXPECT_EQ(value["Image"]["Title"].to_string(), "View from 15th Floor");
  EXPECT_FALSE(value["Image"]["Animated"].to_boolean());

  // Image.Thumbnail object
  EXPECT_EQ(value["Image"]["Thumbnail"].size(), 3);
  EXPECT_TRUE(value["Image"]["Thumbnail"].contains("Url"));
  EXPECT_TRUE(value["Image"]["Thumbnail"].contains("Height"));
  EXPECT_TRUE(value["Image"]["Thumbnail"].contains("Width"));
  EXPECT_TRUE(value["Image"]["Thumbnail"]["Url"].is_string());
  EXPECT_TRUE(value["Image"]["Thumbnail"]["Height"].is_integer());
  EXPECT_TRUE(value["Image"]["Thumbnail"]["Width"].is_integer());
  EXPECT_EQ(value["Image"]["Thumbnail"]["Url"].to_string(),
            "http://www.example.com/image/481989943");
  EXPECT_EQ(value["Image"]["Thumbnail"]["Height"].to_integer(), 125);
  EXPECT_EQ(value["Image"]["Thumbnail"]["Width"].to_integer(), 100);

  // Image.IDs array
  EXPECT_EQ(value["Image"]["IDs"].size(), 4);
  EXPECT_TRUE(value["Image"]["IDs"][0].is_integer());
  EXPECT_TRUE(value["Image"]["IDs"][1].is_integer());
  EXPECT_TRUE(value["Image"]["IDs"][2].is_integer());
  EXPECT_TRUE(value["Image"]["IDs"][3].is_integer());
  EXPECT_EQ(value["Image"]["IDs"][0].to_integer(), 116);
  EXPECT_EQ(value["Image"]["IDs"][1].to_integer(), 943);
  EXPECT_EQ(value["Image"]["IDs"][2].to_integer(), 234);
  EXPECT_EQ(value["Image"]["IDs"][3].to_integer(), 38793);
}

// https://datatracker.ietf.org/doc/html/rfc8259#section-13
TEST(JSON, rfc8259_example_2) {
  sourcemeta::jsontoolkit::JSON value{"[\n"
                                      "{\n"
                                      "\"precision\": \"zip\",\n"
                                      "\"Latitude\":  37.7668,\n"
                                      "\"Longitude\": -122.3959,\n"
                                      "\"Address\":   \"\",\n"
                                      "\"City\":      \"SAN FRANCISCO\",\n"
                                      "\"State\":     \"CA\",\n"
                                      "\"Zip\":       \"94107\",\n"
                                      "\"Country\":   \"US\"\n"
                                      "},\n"
                                      "{\n"
                                      "\"precision\": \"zip\",\n"
                                      "\"Latitude\":  37.371991,\n"
                                      "\"Longitude\": -122.026020,\n"
                                      "\"Address\":   \"\",\n"
                                      "\"City\":      \"SUNNYVALE\",\n"
                                      "\"State\":     \"CA\",\n"
                                      "\"Zip\":       \"94085\",\n"
                                      "\"Country\":   \"US\"\n"
                                      "}\n"
                                      "]"};

  // Type and size
  EXPECT_TRUE(value.is_array());
  EXPECT_EQ(value.size(), 2);
  EXPECT_EQ(std::as_const(value).size(), 2);

  // Type and size
  EXPECT_TRUE(value[0].is_object());
  EXPECT_EQ(value[0].size(), 8);
  EXPECT_EQ(std::as_const(value[0]).size(), 8);

  // Member keys
  EXPECT_TRUE(value[0].contains("precision"));
  EXPECT_TRUE(value[0].contains("Latitude"));
  EXPECT_TRUE(value[0].contains("Longitude"));
  EXPECT_TRUE(value[0].contains("Address"));
  EXPECT_TRUE(value[0].contains("City"));
  EXPECT_TRUE(value[0].contains("State"));
  EXPECT_TRUE(value[0].contains("Zip"));
  EXPECT_TRUE(value[0].contains("Country"));

  // Member types
  EXPECT_TRUE(value[0]["precision"].is_string());
  EXPECT_TRUE(value[0]["Latitude"].is_real());
  EXPECT_TRUE(value[0]["Longitude"].is_real());
  EXPECT_TRUE(value[0]["Address"].is_string());
  EXPECT_TRUE(value[0]["City"].is_string());
  EXPECT_TRUE(value[0]["State"].is_string());
  EXPECT_TRUE(value[0]["Zip"].is_string());
  EXPECT_TRUE(value[0]["Country"].is_string());

  // Member values
  EXPECT_EQ(value[0]["precision"], "zip");
  EXPECT_EQ(value[0]["Latitude"], 37.7668);
  EXPECT_EQ(value[0]["Longitude"], -122.3959);
  EXPECT_EQ(value[0]["Address"], "");
  EXPECT_EQ(value[0]["City"], "SAN FRANCISCO");
  EXPECT_EQ(value[0]["State"], "CA");
  EXPECT_EQ(value[0]["Zip"], "94107");
  EXPECT_EQ(value[0]["Country"], "US");

  // Type and size
  EXPECT_TRUE(value[1].is_object());
  EXPECT_EQ(value[1].size(), 8);
  EXPECT_EQ(std::as_const(value[1]).size(), 8);

  // Member keys
  EXPECT_TRUE(value[1].contains("precision"));
  EXPECT_TRUE(value[1].contains("Latitude"));
  EXPECT_TRUE(value[1].contains("Longitude"));
  EXPECT_TRUE(value[1].contains("Address"));
  EXPECT_TRUE(value[1].contains("City"));
  EXPECT_TRUE(value[1].contains("State"));
  EXPECT_TRUE(value[1].contains("Zip"));
  EXPECT_TRUE(value[1].contains("Country"));

  // Member types
  EXPECT_TRUE(value[1]["precision"].is_string());
  EXPECT_TRUE(value[1]["Latitude"].is_real());
  EXPECT_TRUE(value[1]["Longitude"].is_real());
  EXPECT_TRUE(value[1]["Address"].is_string());
  EXPECT_TRUE(value[1]["City"].is_string());
  EXPECT_TRUE(value[1]["State"].is_string());
  EXPECT_TRUE(value[1]["Zip"].is_string());
  EXPECT_TRUE(value[1]["Country"].is_string());

  // Member values
  EXPECT_EQ(value[1]["precision"], "zip");
  EXPECT_EQ(value[1]["Latitude"], 37.371991);
  EXPECT_EQ(value[1]["Longitude"], -122.026020);
  EXPECT_EQ(value[1]["Address"], "");
  EXPECT_EQ(value[1]["City"], "SUNNYVALE");
  EXPECT_EQ(value[1]["State"], "CA");
  EXPECT_EQ(value[1]["Zip"], "94085");
  EXPECT_EQ(value[1]["Country"], "US");
}

TEST(JSON, array_key_copy_assignment_vector) {
  sourcemeta::jsontoolkit::JSON document{"{ \"foo\": [] }"};
  document.parse();
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document["foo"].is_array());
  EXPECT_EQ(document["foo"].size(), 0);

  sourcemeta::jsontoolkit::JSON first{"1"};
  sourcemeta::jsontoolkit::JSON second{"2"};
  sourcemeta::jsontoolkit::JSON third{"3"};

  first.parse();
  second.parse();
  third.parse();

  std::vector<sourcemeta::jsontoolkit::JSON> list;
  list.push_back(first);
  list.push_back(second);
  list.push_back(third);

  document.assign("foo", list);
  // EXPECT_EQ(document.size(), 1);
  // EXPECT_TRUE(document.contains("foo"));
  // EXPECT_TRUE(document["foo"].is_array());
  // EXPECT_EQ(document["foo"].size(), 3);
  // EXPECT_EQ(document["foo"][0], static_cast<std::int64_t>(1));
  // EXPECT_EQ(document["foo"][1], static_cast<std::int64_t>(2));
  // EXPECT_EQ(document["foo"][2], static_cast<std::int64_t>(3));
}

TEST(JSON, modify_object_after_copy) {
  // Original document
  sourcemeta::jsontoolkit::JSON document{"{ \"x\": 1, \"y\": 2 }"};
  document.parse();
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document.contains("x"));
  EXPECT_TRUE(document.contains("y"));
  EXPECT_EQ(document["x"], static_cast<std::int64_t>(1));
  EXPECT_EQ(document["y"], static_cast<std::int64_t>(2));

  // Make copy
  sourcemeta::jsontoolkit::JSON copy{document};
  EXPECT_EQ(copy.size(), 2);
  EXPECT_TRUE(copy.contains("x"));
  EXPECT_TRUE(copy.contains("y"));
  EXPECT_EQ(copy["x"], static_cast<std::int64_t>(1));
  EXPECT_EQ(copy["y"], static_cast<std::int64_t>(2));

  // Modify copy
  copy.erase("x");
  EXPECT_EQ(copy.size(), 1);
  EXPECT_TRUE(copy.contains("y"));
  EXPECT_EQ(copy["y"], static_cast<std::int64_t>(2));

  // Original document must remain intact
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document.contains("x"));
  EXPECT_TRUE(document.contains("y"));
  EXPECT_EQ(document["x"], static_cast<std::int64_t>(1));
  EXPECT_EQ(document["y"], static_cast<std::int64_t>(2));
}

TEST(JSON, modify_array_after_copy) {
  // Original document
  sourcemeta::jsontoolkit::JSON document{"[1,2,3]"};
  document.parse();
  EXPECT_EQ(document.size(), 3);
  EXPECT_EQ(document[0], static_cast<std::int64_t>(1));
  EXPECT_EQ(document[1], static_cast<std::int64_t>(2));
  EXPECT_EQ(document[2], static_cast<std::int64_t>(3));

  // Make copy
  sourcemeta::jsontoolkit::JSON copy{document};
  EXPECT_EQ(copy.size(), 3);
  EXPECT_EQ(copy[0], static_cast<std::int64_t>(1));
  EXPECT_EQ(copy[1], static_cast<std::int64_t>(2));
  EXPECT_EQ(copy[2], static_cast<std::int64_t>(3));

  // Modify copy
  copy[1] = 5;
  EXPECT_EQ(copy[1], static_cast<std::int64_t>(5));

  // Original document must remain intact
  EXPECT_EQ(document.size(), 3);
  EXPECT_EQ(document[0], static_cast<std::int64_t>(1));
  EXPECT_EQ(document[1], static_cast<std::int64_t>(2));
  EXPECT_EQ(document[2], static_cast<std::int64_t>(3));
}
