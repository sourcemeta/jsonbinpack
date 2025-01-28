#include <gtest/gtest.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/jsonbinpack/runtime.h>

#include <variant>

TEST(JSONBinPack_Loader_v1, BYTE_CHOICE_INDEX_scalars) {
  const sourcemeta::core::JSON input = sourcemeta::core::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "BYTE_CHOICE_INDEX",
    "binpackOptions": {
      "choices": [ 1, 2, 3 ]
    }
  })JSON");

  const auto result{sourcemeta::jsonbinpack::load(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::holds_alternative<BYTE_CHOICE_INDEX>(result));
  EXPECT_EQ(std::get<BYTE_CHOICE_INDEX>(result).choices.size(), 3);
  EXPECT_EQ(std::get<BYTE_CHOICE_INDEX>(result).choices.at(0),
            sourcemeta::core::JSON{1});
  EXPECT_EQ(std::get<BYTE_CHOICE_INDEX>(result).choices.at(1),
            sourcemeta::core::JSON{2});
  EXPECT_EQ(std::get<BYTE_CHOICE_INDEX>(result).choices.at(2),
            sourcemeta::core::JSON{3});
}

TEST(JSONBinPack_Loader_v1, LARGE_CHOICE_INDEX_scalars) {
  const sourcemeta::core::JSON input = sourcemeta::core::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "LARGE_CHOICE_INDEX",
    "binpackOptions": {
      "choices": [ 1, 2, 3 ]
    }
  })JSON");

  const auto result{sourcemeta::jsonbinpack::load(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::holds_alternative<LARGE_CHOICE_INDEX>(result));
  EXPECT_EQ(std::get<LARGE_CHOICE_INDEX>(result).choices.size(), 3);
  EXPECT_EQ(std::get<LARGE_CHOICE_INDEX>(result).choices.at(0),
            sourcemeta::core::JSON{1});
  EXPECT_EQ(std::get<LARGE_CHOICE_INDEX>(result).choices.at(1),
            sourcemeta::core::JSON{2});
  EXPECT_EQ(std::get<LARGE_CHOICE_INDEX>(result).choices.at(2),
            sourcemeta::core::JSON{3});
}

TEST(JSONBinPack_Loader_v1, TOP_LEVEL_BYTE_CHOICE_INDEX_scalars) {
  const sourcemeta::core::JSON input = sourcemeta::core::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "TOP_LEVEL_BYTE_CHOICE_INDEX",
    "binpackOptions": {
      "choices": [ 1, 2, 3 ]
    }
  })JSON");

  const auto result{sourcemeta::jsonbinpack::load(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::holds_alternative<TOP_LEVEL_BYTE_CHOICE_INDEX>(result));
  EXPECT_EQ(std::get<TOP_LEVEL_BYTE_CHOICE_INDEX>(result).choices.size(), 3);
  EXPECT_EQ(std::get<TOP_LEVEL_BYTE_CHOICE_INDEX>(result).choices.at(0),
            sourcemeta::core::JSON{1});
  EXPECT_EQ(std::get<TOP_LEVEL_BYTE_CHOICE_INDEX>(result).choices.at(1),
            sourcemeta::core::JSON{2});
  EXPECT_EQ(std::get<TOP_LEVEL_BYTE_CHOICE_INDEX>(result).choices.at(2),
            sourcemeta::core::JSON{3});
}

TEST(JSONBinPack_Loader_v1, CONST_NONE_scalar) {
  const sourcemeta::core::JSON input = sourcemeta::core::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "CONST_NONE",
    "binpackOptions": {
      "value": 1
    }
  })JSON");

  const auto result{sourcemeta::jsonbinpack::load(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::holds_alternative<CONST_NONE>(result));
  EXPECT_EQ(std::get<CONST_NONE>(result).value, sourcemeta::core::JSON{1});
}

TEST(JSONBinPack_Loader_v1, ANY_PACKED_TYPE_TAG_BYTE_PREFIX) {
  const sourcemeta::core::JSON input = sourcemeta::core::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "binpackOptions": {}
  })JSON");

  const auto result{sourcemeta::jsonbinpack::load(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::holds_alternative<ANY_PACKED_TYPE_TAG_BYTE_PREFIX>(result));
}
