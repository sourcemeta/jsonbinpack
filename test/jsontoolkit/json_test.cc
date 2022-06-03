#include <cstdint> // std::int64_t
#include <gtest/gtest.h>
#include <jsontoolkit/json.h>
#include <stdexcept>   // std::domain_error
#include <type_traits> // std::is_default_constructible
#include <utility>     // std::as_const
#include <vector>      // std::vector

TEST(JSON, default_constructible_is_invalid) {
  EXPECT_TRUE(std::is_default_constructible<
              sourcemeta::jsontoolkit::JSON<std::string>>::value);
  sourcemeta::jsontoolkit::JSON<std::string> document;
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(JSON, proper_copy_equivalence_constructor) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[1,{\"foo\": 1.2},3]"};
  document.parse();
  sourcemeta::jsontoolkit::JSON<std::string> copy{document};
  copy.parse();
  EXPECT_EQ(document, copy);
}

TEST(JSON, proper_copy_equivalence_assignment) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[1,{\"foo\": 1.2},3]"};
  document.parse();
  sourcemeta::jsontoolkit::JSON<std::string> copy = document;
  copy.parse();
  EXPECT_EQ(document, copy);
}

TEST(JSON, set_boolean) {
  sourcemeta::jsontoolkit::JSON<std::string> document{false};
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
  sourcemeta::jsontoolkit::JSON<std::string> document{"true"};
  document.parse();
  EXPECT_EQ(document, true);
}

TEST(JSON, bool_deep_parse_failure) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"tru"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(JSON, int_deep_parse) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"4"};
  document.parse();
  EXPECT_EQ(document, static_cast<std::int64_t>(4));
}

TEST(JSON, int_deep_parse_failure) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"32,2"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(JSON, real_deep_parse) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"3.14"};
  document.parse();
  EXPECT_EQ(document, 3.14);
}

TEST(JSON, real_deep_parse_failure) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"32.2.2"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(JSON, null_deep_parse) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"null"};
  document.parse();
  EXPECT_EQ(document, nullptr);
}

TEST(JSON, null_deep_parse_failure) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"nul"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(json, string_deep_parse) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"foo\""};
  document.parse();
  EXPECT_EQ(document, "foo");
}

TEST(JSON, string_deep_parse_failure) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"foo"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(JSON, array_deep_parse) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[true,false,true]"};
  document.parse();
  EXPECT_EQ(document.size(), 3);
  EXPECT_EQ(std::as_const(document).size(), 3);
}

TEST(JSON, array_deep_parse_failure) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[true,fals,true]"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(JSON, object_deep_parse) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"{\"foo\":2}"};
  document.parse();
  EXPECT_EQ(document.size(), 1);
  EXPECT_EQ(std::as_const(document).size(), 1);
}

TEST(JSON, object_deep_parse_failure) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"{\"foo\":tru}"};
  EXPECT_THROW(document.parse(), std::domain_error);
}

TEST(JSON, not_bool_equality_string) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"foo\""};
  EXPECT_FALSE(document.is_boolean());
  EXPECT_FALSE(document == true);
}

TEST(JSON, not_bool_equality_int) {
  sourcemeta::jsontoolkit::JSON<std::string> document{
      static_cast<std::int64_t>(6)};
  EXPECT_FALSE(document.is_boolean());
  EXPECT_FALSE(document == true);
}

TEST(JSON, at_boolean) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"[true,false,true]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 3);

  EXPECT_TRUE(document.at(0).is_boolean());
  EXPECT_TRUE(document.at(1).is_boolean());
  EXPECT_TRUE(document.at(2).is_boolean());

  EXPECT_EQ(document.at(0), true);
  EXPECT_EQ(document.at(1), false);
  EXPECT_EQ(document.at(2), true);

  document.parse();
  EXPECT_EQ(std::as_const(document).size(), 3);
}

TEST(JSON, boolean_array_iterator) {
  sourcemeta::jsontoolkit::JSON<std::string> value{"[true,false,false]"};
  std::vector<bool> result;

  for (sourcemeta::jsontoolkit::JSON<std::string> &element : value.to_array()) {
    result.push_back(element.to_boolean());
  }

  EXPECT_EQ(result.size(), 3);
  EXPECT_TRUE(result.at(0));
  EXPECT_FALSE(result.at(1));
  EXPECT_FALSE(result.at(2));
}

TEST(JSON, boolean_array_reverse_iterator) {
  sourcemeta::jsontoolkit::JSON<std::string> value{"[true,false,false]"};
  std::vector<bool> result;

  for (auto iterator = value.to_array().rbegin();
       iterator != value.to_array().rend(); iterator++) {
    result.push_back(iterator->to_boolean());
  }

  EXPECT_EQ(result.size(), 3);
  EXPECT_FALSE(result.at(0));
  EXPECT_FALSE(result.at(1));
  EXPECT_TRUE(result.at(2));
}

TEST(JSON, array_padded_parse) {
  sourcemeta::jsontoolkit::JSON<std::string> value{"  [true,false,false]  "};
  EXPECT_TRUE(value.is_array());
}

// https://datatracker.ietf.org/doc/html/rfc8259#section-13
TEST(JSON, rfc8259_example_1) {
  sourcemeta::jsontoolkit::JSON<std::string> value{
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
  EXPECT_TRUE(value.at("Image").is_object());
  EXPECT_EQ(value.at("Image").size(), 6);
  EXPECT_TRUE(value.at("Image").contains("Width"));
  EXPECT_TRUE(value.at("Image").contains("Height"));
  EXPECT_TRUE(value.at("Image").contains("Title"));
  EXPECT_TRUE(value.at("Image").contains("Thumbnail"));
  EXPECT_TRUE(value.at("Image").contains("Animated"));
  EXPECT_TRUE(value.at("Image").contains("IDs"));
  EXPECT_TRUE(value.at("Image").at("Width").is_integer());
  EXPECT_TRUE(value.at("Image").at("Height").is_integer());
  EXPECT_TRUE(value.at("Image").at("Title").is_string());
  EXPECT_TRUE(value.at("Image").at("Thumbnail").is_object());
  EXPECT_TRUE(value.at("Image").at("Animated").is_boolean());
  EXPECT_TRUE(value.at("Image").at("IDs").is_array());
  EXPECT_EQ(value.at("Image").at("Width").to_integer(), 800);
  EXPECT_EQ(value.at("Image").at("Height").to_integer(), 600);
  EXPECT_EQ(value.at("Image").at("Title").to_string(), "View from 15th Floor");
  EXPECT_FALSE(value.at("Image").at("Animated").to_boolean());

  // Image.Thumbnail object
  EXPECT_EQ(value.at("Image").at("Thumbnail").size(), 3);
  EXPECT_TRUE(value.at("Image").at("Thumbnail").contains("Url"));
  EXPECT_TRUE(value.at("Image").at("Thumbnail").contains("Height"));
  EXPECT_TRUE(value.at("Image").at("Thumbnail").contains("Width"));
  EXPECT_TRUE(value.at("Image").at("Thumbnail").at("Url").is_string());
  EXPECT_TRUE(value.at("Image").at("Thumbnail").at("Height").is_integer());
  EXPECT_TRUE(value.at("Image").at("Thumbnail").at("Width").is_integer());
  EXPECT_EQ(value.at("Image").at("Thumbnail").at("Url").to_string(),
            "http://www.example.com/image/481989943");
  EXPECT_EQ(value.at("Image").at("Thumbnail").at("Height").to_integer(), 125);
  EXPECT_EQ(value.at("Image").at("Thumbnail").at("Width").to_integer(), 100);

  // Image.IDs array
  EXPECT_EQ(value.at("Image").at("IDs").size(), 4);
  EXPECT_TRUE(value.at("Image").at("IDs").at(0).is_integer());
  EXPECT_TRUE(value.at("Image").at("IDs").at(1).is_integer());
  EXPECT_TRUE(value.at("Image").at("IDs").at(2).is_integer());
  EXPECT_TRUE(value.at("Image").at("IDs").at(3).is_integer());
  EXPECT_EQ(value.at("Image").at("IDs").at(0).to_integer(), 116);
  EXPECT_EQ(value.at("Image").at("IDs").at(1).to_integer(), 943);
  EXPECT_EQ(value.at("Image").at("IDs").at(2).to_integer(), 234);
  EXPECT_EQ(value.at("Image").at("IDs").at(3).to_integer(), 38793);
}

// https://datatracker.ietf.org/doc/html/rfc8259#section-13
TEST(JSON, rfc8259_example_2) {
  sourcemeta::jsontoolkit::JSON<std::string> value{
      "[\n"
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

  value.parse();

  // Type and size
  EXPECT_TRUE(value.is_array());
  EXPECT_EQ(value.size(), 2);
  EXPECT_EQ(std::as_const(value).size(), 2);

  // Type and size
  EXPECT_TRUE(value.at(0).is_object());
  EXPECT_EQ(value.at(0).size(), 8);
  value.parse();
  EXPECT_EQ(std::as_const(value).at(0).size(), 8);

  // Member keys
  EXPECT_TRUE(value.at(0).contains("precision"));
  EXPECT_TRUE(value.at(0).contains("Latitude"));
  EXPECT_TRUE(value.at(0).contains("Longitude"));
  EXPECT_TRUE(value.at(0).contains("Address"));
  EXPECT_TRUE(value.at(0).contains("City"));
  EXPECT_TRUE(value.at(0).contains("State"));
  EXPECT_TRUE(value.at(0).contains("Zip"));
  EXPECT_TRUE(value.at(0).contains("Country"));

  // Member types
  EXPECT_TRUE(value.at(0).at("precision").is_string());
  EXPECT_TRUE(value.at(0).at("Latitude").is_real());
  EXPECT_TRUE(value.at(0).at("Longitude").is_real());
  EXPECT_TRUE(value.at(0).at("Address").is_string());
  EXPECT_TRUE(value.at(0).at("City").is_string());
  EXPECT_TRUE(value.at(0).at("State").is_string());
  EXPECT_TRUE(value.at(0).at("Zip").is_string());
  EXPECT_TRUE(value.at(0).at("Country").is_string());

  // Member values
  EXPECT_EQ(value.at(0).at("precision"), "zip");
  EXPECT_EQ(value.at(0).at("Latitude"), 37.7668);
  EXPECT_EQ(value.at(0).at("Longitude"), -122.3959);
  EXPECT_EQ(value.at(0).at("Address"), "");
  EXPECT_EQ(value.at(0).at("City"), "SAN FRANCISCO");
  EXPECT_EQ(value.at(0).at("State"), "CA");
  EXPECT_EQ(value.at(0).at("Zip"), "94107");
  EXPECT_EQ(value.at(0).at("Country"), "US");

  // Type and size
  EXPECT_TRUE(value.at(1).is_object());
  EXPECT_EQ(value.at(1).size(), 8);
  // .at() on object/arrays invalidates deep parsing
  value.parse();
  EXPECT_EQ(std::as_const(value).at(1).size(), 8);

  // Member keys
  EXPECT_TRUE(value.at(1).contains("precision"));
  EXPECT_TRUE(value.at(1).contains("Latitude"));
  EXPECT_TRUE(value.at(1).contains("Longitude"));
  EXPECT_TRUE(value.at(1).contains("Address"));
  EXPECT_TRUE(value.at(1).contains("City"));
  EXPECT_TRUE(value.at(1).contains("State"));
  EXPECT_TRUE(value.at(1).contains("Zip"));
  EXPECT_TRUE(value.at(1).contains("Country"));

  // Member types
  EXPECT_TRUE(value.at(1).at("precision").is_string());
  EXPECT_TRUE(value.at(1).at("Latitude").is_real());
  EXPECT_TRUE(value.at(1).at("Longitude").is_real());
  EXPECT_TRUE(value.at(1).at("Address").is_string());
  EXPECT_TRUE(value.at(1).at("City").is_string());
  EXPECT_TRUE(value.at(1).at("State").is_string());
  EXPECT_TRUE(value.at(1).at("Zip").is_string());
  EXPECT_TRUE(value.at(1).at("Country").is_string());

  // Member values
  EXPECT_EQ(value.at(1).at("precision"), "zip");
  EXPECT_EQ(value.at(1).at("Latitude"), 37.371991);
  EXPECT_EQ(value.at(1).at("Longitude"), -122.026020);
  EXPECT_EQ(value.at(1).at("Address"), "");
  EXPECT_EQ(value.at(1).at("City"), "SUNNYVALE");
  EXPECT_EQ(value.at(1).at("State"), "CA");
  EXPECT_EQ(value.at(1).at("Zip"), "94085");
  EXPECT_EQ(value.at(1).at("Country"), "US");
}

TEST(JSON, array_key_copy_assignment_vector) {
  sourcemeta::jsontoolkit::JSON<std::string> document{"{ \"foo\": [] }"};
  document.parse();
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.at("foo").is_array());
  EXPECT_EQ(document.at("foo").size(), 0);

  sourcemeta::jsontoolkit::JSON<std::string> first{"1"};
  sourcemeta::jsontoolkit::JSON<std::string> second{"2"};
  sourcemeta::jsontoolkit::JSON<std::string> third{"3"};

  first.parse();
  second.parse();
  third.parse();

  std::vector<sourcemeta::jsontoolkit::JSON<std::string>> list;
  list.push_back(first);
  list.push_back(second);
  list.push_back(third);

  document.assign("foo", list);
  EXPECT_EQ(document.size(), 1);
  EXPECT_TRUE(document.contains("foo"));
  EXPECT_TRUE(document.at("foo").is_array());
  EXPECT_EQ(document.at("foo").size(), 3);
  EXPECT_EQ(document.at("foo").at(0), static_cast<std::int64_t>(1));
  EXPECT_EQ(document.at("foo").at(1), static_cast<std::int64_t>(2));
  EXPECT_EQ(document.at("foo").at(2), static_cast<std::int64_t>(3));
}

TEST(JSON, modify_object_after_copy) {
  // Original document
  sourcemeta::jsontoolkit::JSON<std::string> document{"{ \"x\": 1, \"y\": 2 }"};
  document.parse();
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document.contains("x"));
  EXPECT_TRUE(document.contains("y"));
  EXPECT_EQ(document.at("x"), static_cast<std::int64_t>(1));
  EXPECT_EQ(document.at("y"), static_cast<std::int64_t>(2));

  // Make copy
  sourcemeta::jsontoolkit::JSON<std::string> copy{document};
  EXPECT_EQ(copy.size(), 2);
  EXPECT_TRUE(copy.contains("x"));
  EXPECT_TRUE(copy.contains("y"));
  EXPECT_EQ(copy.at("x"), static_cast<std::int64_t>(1));
  EXPECT_EQ(copy.at("y"), static_cast<std::int64_t>(2));

  // Modify copy
  copy.erase("x");
  EXPECT_EQ(copy.size(), 1);
  EXPECT_TRUE(copy.contains("y"));
  EXPECT_EQ(copy.at("y"), static_cast<std::int64_t>(2));

  // Original document must remain intact
  EXPECT_EQ(document.size(), 2);
  EXPECT_TRUE(document.contains("x"));
  EXPECT_TRUE(document.contains("y"));
  EXPECT_EQ(document.at("x"), static_cast<std::int64_t>(1));
  EXPECT_EQ(document.at("y"), static_cast<std::int64_t>(2));
}

TEST(JSON, modify_array_after_copy) {
  // Original document
  sourcemeta::jsontoolkit::JSON<std::string> document{"[1,2,3]"};
  document.parse();
  EXPECT_EQ(document.size(), 3);
  EXPECT_EQ(document.at(0), static_cast<std::int64_t>(1));
  EXPECT_EQ(document.at(1), static_cast<std::int64_t>(2));
  EXPECT_EQ(document.at(2), static_cast<std::int64_t>(3));

  // Make copy
  sourcemeta::jsontoolkit::JSON<std::string> copy{document};
  EXPECT_EQ(copy.size(), 3);
  EXPECT_EQ(copy.at(0), static_cast<std::int64_t>(1));
  EXPECT_EQ(copy.at(1), static_cast<std::int64_t>(2));
  EXPECT_EQ(copy.at(2), static_cast<std::int64_t>(3));

  // Modify copy
  copy.assign(1, static_cast<std::int64_t>(5));
  EXPECT_EQ(copy.at(1), static_cast<std::int64_t>(5));

  // Original document must remain intact
  EXPECT_EQ(document.size(), 3);
  EXPECT_EQ(document.at(0), static_cast<std::int64_t>(1));
  EXPECT_EQ(document.at(1), static_cast<std::int64_t>(2));
  EXPECT_EQ(document.at(2), static_cast<std::int64_t>(3));
}
