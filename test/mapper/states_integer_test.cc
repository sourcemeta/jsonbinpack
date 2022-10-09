#include <jsonbinpack/mapper/states/integer.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>
#include <string>

TEST(MapperStates, unbounded_infinity) {
  sourcemeta::jsontoolkit::JSON<std::string> schema(R"JSON({
    "type": "integer"
  })JSON");
  schema.parse();
  std::optional<sourcemeta::jsontoolkit::JSON<std::string>> states{
      sourcemeta::jsonbinpack::mapper::states::integer(schema)};
  EXPECT_FALSE(states.has_value());
  EXPECT_EQ(states, std::nullopt);
}

TEST(MapperStates, only_minimum) {
  sourcemeta::jsontoolkit::JSON<std::string> schema(R"JSON({
    "type": "integer",
    "minimum": 3
  })JSON");
  schema.parse();
  std::optional<sourcemeta::jsontoolkit::JSON<std::string>> states{
      sourcemeta::jsonbinpack::mapper::states::integer(schema)};
  EXPECT_FALSE(states.has_value());
  EXPECT_EQ(states, std::nullopt);
}

TEST(MapperStates, only_maximum) {
  sourcemeta::jsontoolkit::JSON<std::string> schema(R"JSON({
    "type": "integer",
    "maximum": 3
  })JSON");
  schema.parse();
  std::optional<sourcemeta::jsontoolkit::JSON<std::string>> states{
      sourcemeta::jsonbinpack::mapper::states::integer(schema)};
  EXPECT_FALSE(states.has_value());
  EXPECT_EQ(states, std::nullopt);
}

TEST(MapperStates, bounded_positive) {
  sourcemeta::jsontoolkit::JSON<std::string> schema(R"JSON({
    "type": "integer",
    "maximum": 5,
    "minimum": 3
  })JSON");
  schema.parse();
  sourcemeta::jsontoolkit::JSON<std::string> expected("[3,4,5]");
  expected.parse();
  std::optional<sourcemeta::jsontoolkit::JSON<std::string>> states{
      sourcemeta::jsonbinpack::mapper::states::integer(schema)};
  EXPECT_TRUE(states->is_array());
  EXPECT_EQ(states, expected);
}

TEST(MapperStates, bounded_negative) {
  sourcemeta::jsontoolkit::JSON<std::string> schema(R"JSON({
    "type": "integer",
    "maximum": -8,
    "minimum": -10
  })JSON");
  schema.parse();
  sourcemeta::jsontoolkit::JSON<std::string> expected("[-10,-9,-8]");
  expected.parse();
  std::optional<sourcemeta::jsontoolkit::JSON<std::string>> states{
      sourcemeta::jsonbinpack::mapper::states::integer(schema)};
  EXPECT_TRUE(states->is_array());
  EXPECT_EQ(states, expected);
}

TEST(MapperStates, bounded_negative_positive) {
  sourcemeta::jsontoolkit::JSON<std::string> schema(R"JSON({
    "type": "integer",
    "minimum": -3,
    "maximum": 2
  })JSON");
  schema.parse();
  sourcemeta::jsontoolkit::JSON<std::string> expected("[-3,-2,-1,0,1,2]");
  expected.parse();
  std::optional<sourcemeta::jsontoolkit::JSON<std::string>> states{
      sourcemeta::jsonbinpack::mapper::states::integer(schema)};
  EXPECT_TRUE(states->is_array());
  EXPECT_EQ(states, expected);
}

TEST(MapperStates, bounded_equal) {
  sourcemeta::jsontoolkit::JSON<std::string> schema(R"JSON({
    "type": "integer",
    "minimum": 3,
    "maximum": 3
  })JSON");
  schema.parse();
  sourcemeta::jsontoolkit::JSON<std::string> expected("[3]");
  expected.parse();
  std::optional<sourcemeta::jsontoolkit::JSON<std::string>> states{
      sourcemeta::jsonbinpack::mapper::states::integer(schema)};
  EXPECT_TRUE(states->is_array());
  EXPECT_EQ(states, expected);
}

TEST(MapperStates, bounded_impossible) {
  // This is technically a valid JSON Schema that no instance can match against
  sourcemeta::jsontoolkit::JSON<std::string> schema(R"JSON({
    "type": "integer",
    "minimum": 4,
    "maximum": 3
  })JSON");
  schema.parse();
  sourcemeta::jsontoolkit::JSON<std::string> expected("[]");
  expected.parse();
  std::optional<sourcemeta::jsontoolkit::JSON<std::string>> states{
      sourcemeta::jsonbinpack::mapper::states::integer(schema)};
  EXPECT_TRUE(states->is_array());
  EXPECT_EQ(states, expected);
}

TEST(MapperStates, bounded_positive_with_matching_positive_multiplier) {
  sourcemeta::jsontoolkit::JSON<std::string> schema(R"JSON({
    "type": "integer",
    "multipleOf": 2,
    "maximum": 6,
    "minimum": 2
  })JSON");
  schema.parse();
  sourcemeta::jsontoolkit::JSON<std::string> expected("[2,4,6]");
  expected.parse();
  std::optional<sourcemeta::jsontoolkit::JSON<std::string>> states{
      sourcemeta::jsonbinpack::mapper::states::integer(schema)};
  EXPECT_TRUE(states->is_array());
  EXPECT_EQ(states, expected);
}

TEST(MapperStates, bounded_positive_with_matching_negative_multiplier) {
  sourcemeta::jsontoolkit::JSON<std::string> schema(R"JSON({
    "type": "integer",
    "multipleOf": -2,
    "maximum": 6,
    "minimum": 2
  })JSON");
  schema.parse();
  sourcemeta::jsontoolkit::JSON<std::string> expected("[2,4,6]");
  expected.parse();
  std::optional<sourcemeta::jsontoolkit::JSON<std::string>> states{
      sourcemeta::jsonbinpack::mapper::states::integer(schema)};
  EXPECT_TRUE(states->is_array());
  EXPECT_EQ(states, expected);
}

TEST(MapperStates, bounded_positive_with_non_matching_positive_multiplier) {
  sourcemeta::jsontoolkit::JSON<std::string> schema(R"JSON({
    "type": "integer",
    "multipleOf": 3,
    "maximum": 7,
    "minimum": 2
  })JSON");
  schema.parse();
  sourcemeta::jsontoolkit::JSON<std::string> expected("[3,6]");
  expected.parse();
  std::optional<sourcemeta::jsontoolkit::JSON<std::string>> states{
      sourcemeta::jsonbinpack::mapper::states::integer(schema)};
  EXPECT_TRUE(states->is_array());
  EXPECT_EQ(states, expected);
}

TEST(MapperStates, bounded_positive_with_impossible_multiplier) {
  sourcemeta::jsontoolkit::JSON<std::string> schema(R"JSON({
    "type": "integer",
    "multipleOf": 8,
    "maximum": 3,
    "minimum": 1
  })JSON");
  schema.parse();
  sourcemeta::jsontoolkit::JSON<std::string> expected("[]");
  expected.parse();
  std::optional<sourcemeta::jsontoolkit::JSON<std::string>> states{
      sourcemeta::jsonbinpack::mapper::states::integer(schema)};
  EXPECT_TRUE(states->is_array());
  EXPECT_EQ(states, expected);
}

TEST(MapperStates, bounded_with_real_multiplier) {
  sourcemeta::jsontoolkit::JSON<std::string> schema(R"JSON({
    "type": "integer",
    "multipleOf": 1.1,
    "maximum": 3,
    "minimum": 1
  })JSON");
  schema.parse();
  sourcemeta::jsontoolkit::JSON<std::string> expected("[]");
  expected.parse();
  std::optional<sourcemeta::jsontoolkit::JSON<std::string>> states{
      sourcemeta::jsonbinpack::mapper::states::integer(schema)};
  // Not supported for now
  EXPECT_FALSE(states.has_value());
  EXPECT_EQ(states, std::nullopt);
}
