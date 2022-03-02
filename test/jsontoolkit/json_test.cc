#include <gtest/gtest.h>
#include <jsontoolkit/json.h>
#include <vector> // std::vector

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

TEST(JSON, at_boolean) {
  sourcemeta::jsontoolkit::JSON document{"[true,false,true]"};
  EXPECT_TRUE(document.is_array());
  EXPECT_EQ(document.size(), 3);

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
  sourcemeta::jsontoolkit::JSON value{"[true,false,false]"};
  std::vector<bool> result;

  // TODO: Can we hide the Array type somehow?
  for (sourcemeta::jsontoolkit::Array::reverse_iterator iterator =
           value.to_array()->rbegin();
       iterator != value.to_array()->rend(); iterator++) {
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
