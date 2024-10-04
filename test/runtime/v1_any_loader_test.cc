#include <gtest/gtest.h>

#include <sourcemeta/jsonbinpack/runtime.h>
#include <sourcemeta/jsontoolkit/json.h>

#include <variant>

TEST(JSONBinPack_Loader_v1, ANY_PACKED_TYPE_TAG_BYTE_PREFIX) {
  const sourcemeta::jsontoolkit::JSON input =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "binpackOptions": {}
  })JSON");

  const sourcemeta::jsonbinpack::Plan result{
      sourcemeta::jsonbinpack::load(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::holds_alternative<ANY_PACKED_TYPE_TAG_BYTE_PREFIX>(result));
}
