#include <gtest/gtest.h>

#include <sourcemeta/jsonbinpack/compiler_mapper_states.h>
#include <sourcemeta/jsontoolkit/json.h>

#include <set>
#include <string>
#include <vector>

static std::set<std::string> test_vocabularies{
    "https://json-schema.org/draft/2020-12/vocab/core",
    "https://json-schema.org/draft/2020-12/vocab/applicator",
    "https://json-schema.org/draft/2020-12/vocab/unevaluated",
    "https://json-schema.org/draft/2020-12/vocab/validation",
    "https://json-schema.org/draft/2020-12/vocab/meta-data",
    "https://json-schema.org/draft/2020-12/vocab/format-annotation",
    "https://json-schema.org/draft/2020-12/vocab/content"};

TEST(MapperStates_2020_12, unbounded_infinity) {
  const sourcemeta::jsontoolkit::JSON schema =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "type": "integer"
  })JSON");

  const std::optional<std::vector<sourcemeta::jsontoolkit::JSON>> states{
      sourcemeta::jsonbinpack::mapper::states::integer(schema,
                                                       test_vocabularies)};
  EXPECT_FALSE(states.has_value());
}

TEST(MapperStates_2020_12, only_minimum) {
  const sourcemeta::jsontoolkit::JSON schema =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "type": "integer",
    "minimum": 3
  })JSON");

  const std::optional<std::vector<sourcemeta::jsontoolkit::JSON>> states{
      sourcemeta::jsonbinpack::mapper::states::integer(schema,
                                                       test_vocabularies)};
  EXPECT_FALSE(states.has_value());
}

TEST(MapperStates_2020_12, only_maximum) {
  const sourcemeta::jsontoolkit::JSON schema =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "type": "integer",
    "maximum": 3
  })JSON");

  const std::optional<std::vector<sourcemeta::jsontoolkit::JSON>> states{
      sourcemeta::jsonbinpack::mapper::states::integer(schema,
                                                       test_vocabularies)};
  EXPECT_FALSE(states.has_value());
}

TEST(MapperStates_2020_12, bounded_positive) {
  const sourcemeta::jsontoolkit::JSON schema =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "type": "integer",
    "maximum": 5,
    "minimum": 3
  })JSON");

  const std::optional<std::vector<sourcemeta::jsontoolkit::JSON>> states{
      sourcemeta::jsonbinpack::mapper::states::integer(schema,
                                                       test_vocabularies)};
  EXPECT_TRUE(states.has_value());
  EXPECT_EQ(states->size(), 3);
  EXPECT_EQ(states->at(0).to_integer(), 3);
  EXPECT_EQ(states->at(1).to_integer(), 4);
  EXPECT_EQ(states->at(2).to_integer(), 5);
}

TEST(MapperStates_2020_12, bounded_negative) {
  const sourcemeta::jsontoolkit::JSON schema =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "type": "integer",
    "maximum": -8,
    "minimum": -10
  })JSON");

  const std::optional<std::vector<sourcemeta::jsontoolkit::JSON>> states{
      sourcemeta::jsonbinpack::mapper::states::integer(schema,
                                                       test_vocabularies)};
  EXPECT_TRUE(states.has_value());
  EXPECT_EQ(states->size(), 3);
  EXPECT_EQ(states->at(0).to_integer(), -10);
  EXPECT_EQ(states->at(1).to_integer(), -9);
  EXPECT_EQ(states->at(2).to_integer(), -8);
}

TEST(MapperStates_2020_12, bounded_negative_positive) {
  const sourcemeta::jsontoolkit::JSON schema =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "type": "integer",
    "minimum": -3,
    "maximum": 2
  })JSON");

  const std::optional<std::vector<sourcemeta::jsontoolkit::JSON>> states{
      sourcemeta::jsonbinpack::mapper::states::integer(schema,
                                                       test_vocabularies)};
  EXPECT_TRUE(states.has_value());
  EXPECT_EQ(states->size(), 6);
  EXPECT_EQ(states->at(0).to_integer(), -3);
  EXPECT_EQ(states->at(1).to_integer(), -2);
  EXPECT_EQ(states->at(2).to_integer(), -1);
  EXPECT_EQ(states->at(3).to_integer(), 0);
  EXPECT_EQ(states->at(4).to_integer(), 1);
  EXPECT_EQ(states->at(5).to_integer(), 2);
}

TEST(MapperStates_2020_12, bounded_equal) {
  const sourcemeta::jsontoolkit::JSON schema =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "type": "integer",
    "minimum": 3,
    "maximum": 3
  })JSON");

  const std::optional<std::vector<sourcemeta::jsontoolkit::JSON>> states{
      sourcemeta::jsonbinpack::mapper::states::integer(schema,
                                                       test_vocabularies)};
  EXPECT_TRUE(states.has_value());
  EXPECT_EQ(states->size(), 1);
  EXPECT_EQ(states->at(0).to_integer(), 3);
}

TEST(MapperStates_2020_12, bounded_impossible) {
  // This is technically a valid JSON Schema that no instance can match against
  const sourcemeta::jsontoolkit::JSON schema =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "type": "integer",
    "minimum": 4,
    "maximum": 3
  })JSON");

  const std::optional<std::vector<sourcemeta::jsontoolkit::JSON>> states{
      sourcemeta::jsonbinpack::mapper::states::integer(schema,
                                                       test_vocabularies)};
  EXPECT_TRUE(states.has_value());
  EXPECT_TRUE(states->empty());
}

TEST(MapperStates_2020_12, bounded_positive_with_matching_positive_multiplier) {
  const sourcemeta::jsontoolkit::JSON schema =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "type": "integer",
    "multipleOf": 2,
    "maximum": 6,
    "minimum": 2
  })JSON");

  const std::optional<std::vector<sourcemeta::jsontoolkit::JSON>> states{
      sourcemeta::jsonbinpack::mapper::states::integer(schema,
                                                       test_vocabularies)};
  EXPECT_TRUE(states.has_value());
  EXPECT_EQ(states->size(), 3);
  EXPECT_EQ(states->at(0).to_integer(), 2);
  EXPECT_EQ(states->at(1).to_integer(), 4);
  EXPECT_EQ(states->at(2).to_integer(), 6);
}

TEST(MapperStates_2020_12, bounded_positive_with_matching_negative_multiplier) {
  const sourcemeta::jsontoolkit::JSON schema =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "type": "integer",
    "multipleOf": -2,
    "maximum": 6,
    "minimum": 2
  })JSON");

  const std::optional<std::vector<sourcemeta::jsontoolkit::JSON>> states{
      sourcemeta::jsonbinpack::mapper::states::integer(schema,
                                                       test_vocabularies)};
  EXPECT_TRUE(states.has_value());
  EXPECT_EQ(states->size(), 3);
  EXPECT_EQ(states->at(0).to_integer(), 2);
  EXPECT_EQ(states->at(1).to_integer(), 4);
  EXPECT_EQ(states->at(2).to_integer(), 6);
}

TEST(MapperStates_2020_12,
     bounded_positive_with_non_matching_positive_multiplier) {
  const sourcemeta::jsontoolkit::JSON schema =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "type": "integer",
    "multipleOf": 3,
    "maximum": 7,
    "minimum": 2
  })JSON");

  const std::optional<std::vector<sourcemeta::jsontoolkit::JSON>> states{
      sourcemeta::jsonbinpack::mapper::states::integer(schema,
                                                       test_vocabularies)};
  EXPECT_TRUE(states.has_value());
  EXPECT_EQ(states->size(), 2);
  EXPECT_EQ(states->at(0).to_integer(), 3);
  EXPECT_EQ(states->at(1).to_integer(), 6);
}

TEST(MapperStates_2020_12, bounded_positive_with_impossible_multiplier) {
  const sourcemeta::jsontoolkit::JSON schema =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "type": "integer",
    "multipleOf": 8,
    "maximum": 3,
    "minimum": 1
  })JSON");

  const std::optional<std::vector<sourcemeta::jsontoolkit::JSON>> states{
      sourcemeta::jsonbinpack::mapper::states::integer(schema,
                                                       test_vocabularies)};
  EXPECT_TRUE(states.has_value());
  EXPECT_TRUE(states->empty());
}

TEST(MapperStates_2020_12, bounded_with_real_multiplier) {
  const sourcemeta::jsontoolkit::JSON schema =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "type": "integer",
    "multipleOf": 1.1,
    "maximum": 3,
    "minimum": 1
  })JSON");

  const std::optional<std::vector<sourcemeta::jsontoolkit::JSON>> states{
      sourcemeta::jsonbinpack::mapper::states::integer(schema,
                                                       test_vocabularies)};
  EXPECT_FALSE(states.has_value());
}
