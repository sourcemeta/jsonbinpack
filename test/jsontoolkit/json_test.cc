#include <gtest/gtest.h>
#include <vector> // std::vector
#include <string_view> // std::string_view
#include <jsontoolkit/json.h>

TEST(JSON, true_bool) {
  sourcemeta::jsontoolkit::JSON document {true};
  EXPECT_TRUE(document.is_boolean());
  EXPECT_TRUE(document.to_boolean());
}

TEST(JSON, false_bool) {
  sourcemeta::jsontoolkit::JSON document {false};
  EXPECT_TRUE(document.is_boolean());
  EXPECT_FALSE(document.to_boolean());
}

TEST(JSON, set_boolean) {
  sourcemeta::jsontoolkit::JSON document {false};
  EXPECT_TRUE(document.is_boolean());
  EXPECT_FALSE(document.to_boolean());
  document.set_boolean(true);
  EXPECT_TRUE(document.is_boolean());
  EXPECT_TRUE(document.to_boolean());
  document.set_boolean(false);
  EXPECT_TRUE(document.is_boolean());
  EXPECT_FALSE(document.to_boolean());
}

TEST(JSON, at_boolean) {
  sourcemeta::jsontoolkit::JSON document {std::string_view("[true,false,true]")};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 3);

  EXPECT_TRUE(document.at(0).is_boolean());
  EXPECT_TRUE(document.at(1).is_boolean());
  EXPECT_TRUE(document.at(2).is_boolean());

  EXPECT_TRUE(document.at(0).to_boolean());
  EXPECT_FALSE(document.at(1).to_boolean());
  EXPECT_TRUE(document.at(2).to_boolean());
}

TEST(JSON, boolean_array_iterator) {
  sourcemeta::jsontoolkit::JSON value {std::string_view("[true,false,false]")};
  std::vector<bool> result;

  // TODO: Can we make range for loops nicer?
  for (sourcemeta::jsontoolkit::JSON &element : *(value.to_array())) {
    result.push_back(element.to_boolean());
  }

  EXPECT_EQ(result.size(), 3);
  EXPECT_TRUE(result.at(0));
  EXPECT_FALSE(result.at(1));
  EXPECT_FALSE(result.at(2));
}

TEST(JSON, boolean_array_reverse_iterator) {
  sourcemeta::jsontoolkit::JSON value {std::string_view("[true,false,false]")};
  std::vector<bool> result;

  // TODO: Can we hide the Array type somehow?
  for (sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON>::reverse_iterator
      iterator = value.to_array()->rbegin(); iterator != value.to_array()->rend(); iterator++) {
    result.push_back(iterator->to_boolean());
  }

  EXPECT_EQ(result.size(), 3);
  EXPECT_FALSE(result.at(0));
  EXPECT_FALSE(result.at(1));
  EXPECT_TRUE(result.at(2));
}

TEST(JSON, array_padded_parse) {
  sourcemeta::jsontoolkit::JSON value {std::string_view("  [true,false,false]  ")};
  EXPECT_TRUE(value.is_array());
}
