#include <gtest/gtest.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/jsonbinpack/runtime.h>

#include <variant>

TEST(JSONBinPack_Loader_v1, DOUBLE_VARINT_TUPLE) {
  const sourcemeta::core::JSON input = sourcemeta::core::parse_json(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "DOUBLE_VARINT_TUPLE",
    "binpackOptions": {}
  })JSON");

  const auto result{sourcemeta::jsonbinpack::load(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::holds_alternative<DOUBLE_VARINT_TUPLE>(result));
}
