#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>
#include <jsontoolkit/json.h>

TEST(jsontoolkit_JSON, EmptyObjectIsObject) {
  sourcemeta::jsontoolkit::JSON document{"{}"};
  EXPECT_TRUE(document.is_object());
}

TEST(jsontoolkit_JSON, EmptyArrayIsObject) {
  sourcemeta::jsontoolkit::JSON document{"[]"};
  EXPECT_FALSE(document.is_object());
}

TEST(jsontoolkit_JSON, EmptyObjectIsArray) {
  sourcemeta::jsontoolkit::JSON document{"{}"};
  EXPECT_FALSE(document.is_array());
}

TEST(jsontoolkit_JSON, EmptyArrayIsArray) {
  sourcemeta::jsontoolkit::JSON document{"[]"};
  EXPECT_TRUE(document.is_array());
}

TEST(jsontoolkit_JSON, ArrayIsStructural) {
  sourcemeta::jsontoolkit::JSON document{"[1,2,3]"};
  EXPECT_TRUE(document.is_structural());
}

TEST(jsontoolkit_JSON, ObjectIsStructural) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":2}"};
  EXPECT_TRUE(document.is_structural());
}

TEST(jsontoolkit_JSON, StringIsStructural) {
  sourcemeta::jsontoolkit::JSON document{"\"foo\""};
  EXPECT_FALSE(document.is_structural());
}

TEST(jsontoolkit_JSON, IntegerIsStructural) {
  sourcemeta::jsontoolkit::JSON document{"3"};
  EXPECT_FALSE(document.is_structural());
}

TEST(jsontoolkit_JSON, BooleanIsStructural) {
  sourcemeta::jsontoolkit::JSON document{"false"};
  EXPECT_FALSE(document.is_structural());
}

TEST(jsontoolkit_JSON, FloatIsStructural) {
  sourcemeta::jsontoolkit::JSON document{"3.14"};
  EXPECT_FALSE(document.is_structural());
}

TEST(jsontoolkit_JSON, NullIsStructural) {
  sourcemeta::jsontoolkit::JSON document{"null"};
  EXPECT_FALSE(document.is_structural());
}

TEST(jsontoolkit_JSON, TrueIsBoolean) {
  sourcemeta::jsontoolkit::JSON document{"true"};
  EXPECT_TRUE(document.is_boolean());
}

TEST(jsontoolkit_JSON, FalseIsBoolean) {
  sourcemeta::jsontoolkit::JSON document{"false"};
  EXPECT_TRUE(document.is_boolean());
}

TEST(jsontoolkit_JSON, NullIsBoolean) {
  sourcemeta::jsontoolkit::JSON document{"null"};
  EXPECT_FALSE(document.is_boolean());
}

TEST(jsontoolkit_JSON, NullIsNull) {
  sourcemeta::jsontoolkit::JSON document{"null"};
  EXPECT_TRUE(document.is_null());
}

TEST(jsontoolkit_JSON, BooleanIsNull) {
  sourcemeta::jsontoolkit::JSON document_true{"true"};
  sourcemeta::jsontoolkit::JSON document_false{"false"};
  EXPECT_FALSE(document_true.is_null());
  EXPECT_FALSE(document_false.is_null());
}

TEST(jsontoolkit_JSON, PositiveIntegerIsNumber) {
  sourcemeta::jsontoolkit::JSON document{"5"};
  EXPECT_TRUE(document.is_number());
}

TEST(jsontoolkit_JSON, NegativeIntegerIsNumber) {
  sourcemeta::jsontoolkit::JSON document{"-5"};
  EXPECT_TRUE(document.is_number());
}

TEST(jsontoolkit_JSON, PositiveRealIsNumber) {
  sourcemeta::jsontoolkit::JSON document{"3.5"};
  EXPECT_TRUE(document.is_number());
}

TEST(jsontoolkit_JSON, NegativeRealIsNumber) {
  sourcemeta::jsontoolkit::JSON document{"-0.5"};
  EXPECT_TRUE(document.is_number());
}

TEST(jsontoolkit_JSON, BooleanRealIsNumber) {
  sourcemeta::jsontoolkit::JSON document{"true"};
  EXPECT_FALSE(document.is_number());
}

TEST(jsontoolkit_JSON, StringIsNumber) {
  sourcemeta::jsontoolkit::JSON document{"\"4\""};
  EXPECT_FALSE(document.is_number());
}

TEST(jsontoolkit_JSON, InvalidDocument) {
  EXPECT_THROW({
    sourcemeta::jsontoolkit::JSON document{"{foo"};
  }, std::invalid_argument);
}

TEST(jsontoolkit_JSON, PositiveIntegerIsInteger) {
  sourcemeta::jsontoolkit::JSON document{"5"};
  EXPECT_TRUE(document.is_integer());
}

TEST(jsontoolkit_JSON, NegativeIntegerIsInteger) {
  sourcemeta::jsontoolkit::JSON document{"-5"};
  EXPECT_TRUE(document.is_integer());
}

TEST(jsontoolkit_JSON, ZeroIntegerIsInteger) {
  sourcemeta::jsontoolkit::JSON document{"0"};
  EXPECT_TRUE(document.is_integer());
}

TEST(jsontoolkit_JSON, PositiveRealIsInteger) {
  sourcemeta::jsontoolkit::JSON document{"3.5"};
  EXPECT_FALSE(document.is_integer());
}

TEST(jsontoolkit_JSON, NegativeRealIsInteger) {
  sourcemeta::jsontoolkit::JSON document{"-0.5"};
  EXPECT_FALSE(document.is_integer());
}

TEST(jsontoolkit_JSON, StringIsInteger) {
  sourcemeta::jsontoolkit::JSON document{"\"4\""};
  EXPECT_FALSE(document.is_integer());
}

TEST(jsontoolkit_JSON, IntegerStringIsString) {
  sourcemeta::jsontoolkit::JSON document{"\"4\""};
  EXPECT_TRUE(document.is_string());
}

TEST(jsontoolkit_JSON, BooleanIsString) {
  sourcemeta::jsontoolkit::JSON document{"true"};
  EXPECT_FALSE(document.is_string());
}

TEST(jsontoolkit_JSON, EmptyStringLength) {
  sourcemeta::jsontoolkit::JSON document{"\"\""};
  EXPECT_EQ(document.length(), 0);
}

TEST(jsontoolkit_JSON, OneCharacterStringLength) {
  sourcemeta::jsontoolkit::JSON document{"\"x\""};
  EXPECT_EQ(document.length(), 1);
}

TEST(jsontoolkit_JSON, SmallStringLength) {
  sourcemeta::jsontoolkit::JSON document{"\"foo bar\""};
  EXPECT_EQ(document.length(), 7);
}

TEST(jsontoolkit_JSON, EmptyArrayLength) {
  sourcemeta::jsontoolkit::JSON document{"[]"};
  EXPECT_EQ(document.length(), 0);
}

TEST(jsontoolkit_JSON, OneItemArrayLength) {
  sourcemeta::jsontoolkit::JSON document{"[1]"};
  EXPECT_EQ(document.length(), 1);
}

TEST(jsontoolkit_JSON, SmallArrayLength) {
  sourcemeta::jsontoolkit::JSON document{"[1,2,3,4,5]"};
  EXPECT_EQ(document.length(), 5);
}

TEST(jsontoolkit_JSON, EmptyObjectLength) {
  sourcemeta::jsontoolkit::JSON document{"{}"};
  EXPECT_EQ(document.length(), 0);
}

TEST(jsontoolkit_JSON, OneItemObjectLength) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":1}"};
  EXPECT_EQ(document.length(), 1);
}

TEST(jsontoolkit_JSON, SmallObjectLength) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":1,\"bar\":2,\"baz\":3}"};
  EXPECT_EQ(document.length(), 3);
}

TEST(jsontoolkit_JSON, BooleanLength) {
  sourcemeta::jsontoolkit::JSON document{"true"};
  EXPECT_THROW({
    document.length();
  }, std::logic_error);
}

TEST(jsontoolkit_JSON, NullLength) {
  sourcemeta::jsontoolkit::JSON document{"null"};
  EXPECT_THROW({
    document.length();
  }, std::logic_error);
}

TEST(jsontoolkit_JSON, IntegerLength) {
  sourcemeta::jsontoolkit::JSON document{"4"};
  EXPECT_THROW({
    document.length();
  }, std::logic_error);
}

TEST(jsontoolkit_JSON, TrueToBoolean) {
  sourcemeta::jsontoolkit::JSON document{"true"};
  EXPECT_EQ(document.to_boolean(), true);
}

TEST(jsontoolkit_JSON, FalseToBoolean) {
  sourcemeta::jsontoolkit::JSON document{"false"};
  EXPECT_EQ(document.to_boolean(), false);
}

TEST(jsontoolkit_JSON, NullToBoolean) {
  sourcemeta::jsontoolkit::JSON document{"null"};
  EXPECT_THROW({
    document.to_boolean();
  }, std::logic_error);
}

TEST(jsontoolkit_JSON, EmptyStringToString) {
  sourcemeta::jsontoolkit::JSON document{"\"\""};
  EXPECT_EQ(document.to_string(), "");
}

TEST(jsontoolkit_JSON, SmallStringToString) {
  sourcemeta::jsontoolkit::JSON document{"\"foo\""};
  EXPECT_EQ(document.to_string(), "foo");
}

TEST(jsontoolkit_JSON, NullToString) {
  sourcemeta::jsontoolkit::JSON document{"null"};
  EXPECT_THROW({
    document.to_string();
  }, std::logic_error);
}

TEST(jsontoolkit_JSON, PositiveIntegerToInteger) {
  sourcemeta::jsontoolkit::JSON document{"5"};
  EXPECT_EQ(document.to_integer(), 5);
}

TEST(jsontoolkit_JSON, ZeroToInteger) {
  sourcemeta::jsontoolkit::JSON document{"0"};
  EXPECT_EQ(document.to_integer(), 0);
}

TEST(jsontoolkit_JSON, NegativeIntegerToInteger) {
  sourcemeta::jsontoolkit::JSON document{"-3"};
  EXPECT_EQ(document.to_integer(), -3);
}

TEST(jsontoolkit_JSON, RealToInteger) {
  sourcemeta::jsontoolkit::JSON document{"3.14"};
  EXPECT_THROW({
    document.to_integer();
  }, std::logic_error);
}

TEST(jsontoolkit_JSON, PositiveIntegerToDouble) {
  sourcemeta::jsontoolkit::JSON document{"5"};
  EXPECT_EQ(document.to_double(), 5);
}

TEST(jsontoolkit_JSON, ZeroToDouble) {
  sourcemeta::jsontoolkit::JSON document{"0"};
  EXPECT_EQ(document.to_double(), 0);
}

TEST(jsontoolkit_JSON, NegativeIntegerToDouble) {
  sourcemeta::jsontoolkit::JSON document{"-3"};
  EXPECT_EQ(document.to_double(), -3);
}

TEST(jsontoolkit_JSON, NegativeRealToDouble) {
  sourcemeta::jsontoolkit::JSON document{"-110"};
  EXPECT_EQ(document.to_double(), -110);
}

TEST(jsontoolkit_JSON, PositiveRealToDouble) {
  sourcemeta::jsontoolkit::JSON document{"150.345"};
  EXPECT_EQ(document.to_double(), 150.345);
}

TEST(jsontoolkit_JSON, ArrayStringIntegerAt) {
  sourcemeta::jsontoolkit::JSON document{"[\"foo\",3,\"baz\"]"};
  sourcemeta::jsontoolkit::JSON element1 = document.at(0);
  sourcemeta::jsontoolkit::JSON element2 = document.at(1);
  EXPECT_TRUE(element1.is_string());
  EXPECT_TRUE(element2.is_integer());
  EXPECT_EQ(element1.to_string(), "foo");
  EXPECT_EQ(element2.to_integer(), 3);
}

TEST(jsontoolkit_JSON, ArrayOutOfBoundsAt) {
  sourcemeta::jsontoolkit::JSON document{"[\"foo\",3,\"baz\"]"};
  EXPECT_THROW({
    sourcemeta::jsontoolkit::JSON element = document.at(3);
  }, std::out_of_range);
}

TEST(jsontoolkit_JSON, ArrayKeyIndex) {
  sourcemeta::jsontoolkit::JSON document{"[\"foo\",3,\"baz\"]"};
  EXPECT_THROW({
    sourcemeta::jsontoolkit::JSON element = document.at("foo");
  }, std::logic_error);
}

TEST(jsontoolkit_JSON, ArrayHas) {
  sourcemeta::jsontoolkit::JSON document{"[\"foo\",3,\"baz\"]"};
  EXPECT_TRUE(document.has(0));
  EXPECT_TRUE(document.has(1));
  EXPECT_TRUE(document.has(2));
  EXPECT_FALSE(document.has(3));
}

TEST(jsontoolkit_JSON, ObjectHas) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":1,\"bar\":2}"};
  EXPECT_TRUE(document.has("foo"));
  EXPECT_TRUE(document.has("bar"));
  EXPECT_FALSE(document.has("baz"));
  EXPECT_FALSE(document.has(""));
}

TEST(jsontoolkit_JSON, ObjectStringIntegerAt) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":\"baz\",\"bar\":2}"};
  sourcemeta::jsontoolkit::JSON element1 = document.at("foo");
  sourcemeta::jsontoolkit::JSON element2 = document.at("bar");
  EXPECT_TRUE(element1.is_string());
  EXPECT_TRUE(element2.is_integer());
  EXPECT_EQ(element1.to_string(), "baz");
  EXPECT_EQ(element2.to_integer(), 2);
}

TEST(jsontoolkit_JSON, ObjectOutOfBoundsAt) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":\"baz\",\"bar\":2}"};
  EXPECT_THROW({
    sourcemeta::jsontoolkit::JSON element = document.at("xxx");
  }, std::out_of_range);
}

TEST(jsontoolkit_JSON, ObjectIndexAt) {
  sourcemeta::jsontoolkit::JSON document{"{\"foo\":\"baz\",\"bar\":2}"};
  EXPECT_THROW({
    sourcemeta::jsontoolkit::JSON element = document.at(0);
  }, std::logic_error);
}

TEST(jsontoolkit_JSON, ArrayReferenceIterator) {
  sourcemeta::jsontoolkit::JSON document{"[\"foo\",\"bar\",\"baz\"]"};
  std::vector<std::string> result;
  for (sourcemeta::jsontoolkit::JSON &element : document) {
    result.push_back(element.to_string());
  }

  EXPECT_EQ(result.size(), 3);
  EXPECT_EQ(result.at(0), "foo");
  EXPECT_EQ(result.at(1), "bar");
  EXPECT_EQ(result.at(2), "baz");
}
