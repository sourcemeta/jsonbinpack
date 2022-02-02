#include <gtest/gtest.h>
#include <vector> // std::vector
#include <functional> // std::reference_wrapper
#include <jsontoolkit/json.h>

TEST(Boolean, true_bool) {
  sourcemeta::jsontoolkit::JSON document {true};
  EXPECT_TRUE(document.is_boolean());
  EXPECT_TRUE(document.to_boolean());
}

TEST(Boolean, false_bool) {
  sourcemeta::jsontoolkit::JSON document {false};
  EXPECT_TRUE(document.is_boolean());
  EXPECT_FALSE(document.to_boolean());
}

TEST(Boolean, set) {
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

TEST(Array, BooleanArrayAt) {
  sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON> document {"[true,false,true]"};
  EXPECT_EQ(document.size(), 3);
  EXPECT_TRUE(document.at(0).to_boolean());
  EXPECT_FALSE(document.at(1).to_boolean());
  EXPECT_TRUE(document.at(2).to_boolean());
}

TEST(JSON, BooleanTrue) {
  sourcemeta::jsontoolkit::JSON document {true};
  EXPECT_TRUE(document.is_boolean());
  EXPECT_TRUE(document.to_boolean());
  EXPECT_FALSE(document.is_array());
}

TEST(JSON, BooleanFalse) {
  sourcemeta::jsontoolkit::JSON document {false};
  EXPECT_TRUE(document.is_boolean());
  EXPECT_FALSE(document.to_boolean());
  EXPECT_FALSE(document.is_array());
}

TEST(JSON, BooleanConstructor) {
  sourcemeta::jsontoolkit::Boolean<sourcemeta::jsontoolkit::JSON> value {true};
  sourcemeta::jsontoolkit::JSON document {value};
  EXPECT_TRUE(document.is_boolean());
  EXPECT_TRUE(document.to_boolean());
}

TEST(JSON, BooleanArrayAt) {
  sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON> value {"[true,false,true]"};
  sourcemeta::jsontoolkit::JSON document {value};
  EXPECT_TRUE(document.is_array());

  EXPECT_TRUE(document.at(0).is_boolean());
  EXPECT_TRUE(document.at(1).is_boolean());
  EXPECT_TRUE(document.at(2).is_boolean());

  EXPECT_TRUE(document.at(0).to_boolean());
  EXPECT_FALSE(document.at(1).to_boolean());
  EXPECT_TRUE(document.at(2).to_boolean());
}

TEST(JSON, BooleanArrayIterator) {
  sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON> value {"[true,false,false]"};
  std::vector<bool> result;

  for (sourcemeta::jsontoolkit::JSON &element : value) {
    result.push_back(element.to_boolean());
  }

  EXPECT_EQ(result.size(), 3);
  EXPECT_TRUE(result.at(0));
  EXPECT_FALSE(result.at(1));
  EXPECT_FALSE(result.at(2));
}

TEST(JSON, BooleanArrayReverseIterator) {
  sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON> value {"[true,false,false]"};
  std::vector<bool> result;

  for (sourcemeta::jsontoolkit::Array<sourcemeta::jsontoolkit::JSON>::reverse_iterator
      iterator = value.rbegin(); iterator != value.rend(); iterator++) {
    result.push_back(iterator->to_boolean());
  }

  EXPECT_EQ(result.size(), 3);
  EXPECT_FALSE(result.at(0));
  EXPECT_FALSE(result.at(1));
  EXPECT_TRUE(result.at(2));
}

TEST(JSON, ArrayParsePadded) {
  sourcemeta::jsontoolkit::JSON value {std::string_view("  [true,false,false]  ")};
  EXPECT_TRUE(value.is_array());
}
