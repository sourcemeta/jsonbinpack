#include <jsonbinpack/parser/parser.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>
#include <variant>

TEST(Parser_v1, BYTE_CHOICE_INDEX_scalars) {
  const sourcemeta::jsontoolkit::JSON input{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v1.json",
    "name": "BYTE_CHOICE_INDEX",
    "options": {
      "choices": [ 1, 2, 3 ]
    }
  })JSON")};

  const sourcemeta::jsonbinpack::Encoding result{
      sourcemeta::jsonbinpack::parse(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::holds_alternative<BYTE_CHOICE_INDEX>(result));
  EXPECT_EQ(std::get<BYTE_CHOICE_INDEX>(result).choices.size(), 3);
  EXPECT_EQ(std::get<BYTE_CHOICE_INDEX>(result).choices.at(0),
            sourcemeta::jsontoolkit::from(1));
  EXPECT_EQ(std::get<BYTE_CHOICE_INDEX>(result).choices.at(1),
            sourcemeta::jsontoolkit::from(2));
  EXPECT_EQ(std::get<BYTE_CHOICE_INDEX>(result).choices.at(2),
            sourcemeta::jsontoolkit::from(3));
}

TEST(Parser_v1, LARGE_CHOICE_INDEX_scalars) {
  const sourcemeta::jsontoolkit::JSON input{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v1.json",
    "name": "LARGE_CHOICE_INDEX",
    "options": {
      "choices": [ 1, 2, 3 ]
    }
  })JSON")};

  const sourcemeta::jsonbinpack::Encoding result{
      sourcemeta::jsonbinpack::parse(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::holds_alternative<LARGE_CHOICE_INDEX>(result));
  EXPECT_EQ(std::get<LARGE_CHOICE_INDEX>(result).choices.size(), 3);
  EXPECT_EQ(std::get<LARGE_CHOICE_INDEX>(result).choices.at(0),
            sourcemeta::jsontoolkit::from(1));
  EXPECT_EQ(std::get<LARGE_CHOICE_INDEX>(result).choices.at(1),
            sourcemeta::jsontoolkit::from(2));
  EXPECT_EQ(std::get<LARGE_CHOICE_INDEX>(result).choices.at(2),
            sourcemeta::jsontoolkit::from(3));
}

TEST(Parser_v1, TOP_LEVEL_BYTE_CHOICE_INDEX_scalars) {
  const sourcemeta::jsontoolkit::JSON input{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v1.json",
    "name": "TOP_LEVEL_BYTE_CHOICE_INDEX",
    "options": {
      "choices": [ 1, 2, 3 ]
    }
  })JSON")};

  const sourcemeta::jsonbinpack::Encoding result{
      sourcemeta::jsonbinpack::parse(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::holds_alternative<TOP_LEVEL_BYTE_CHOICE_INDEX>(result));
  EXPECT_EQ(std::get<TOP_LEVEL_BYTE_CHOICE_INDEX>(result).choices.size(), 3);
  EXPECT_EQ(std::get<TOP_LEVEL_BYTE_CHOICE_INDEX>(result).choices.at(0),
            sourcemeta::jsontoolkit::from(1));
  EXPECT_EQ(std::get<TOP_LEVEL_BYTE_CHOICE_INDEX>(result).choices.at(1),
            sourcemeta::jsontoolkit::from(2));
  EXPECT_EQ(std::get<TOP_LEVEL_BYTE_CHOICE_INDEX>(result).choices.at(2),
            sourcemeta::jsontoolkit::from(3));
}

TEST(Parser_v1, CONST_NONE_scalar) {
  const sourcemeta::jsontoolkit::JSON input{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v1.json",
    "name": "CONST_NONE",
    "options": {
      "value": 1
    }
  })JSON")};

  const sourcemeta::jsonbinpack::Encoding result{
      sourcemeta::jsonbinpack::parse(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::holds_alternative<CONST_NONE>(result));
  EXPECT_EQ(std::get<CONST_NONE>(result).value,
            sourcemeta::jsontoolkit::from(1));
}
