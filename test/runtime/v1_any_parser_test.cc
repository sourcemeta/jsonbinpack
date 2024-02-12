#include <gtest/gtest.h>

#include <sourcemeta/jsonbinpack/runtime.h>
#include <sourcemeta/jsontoolkit/json.h>

#include <variant>

TEST(JSONBinPack_Parser_v1, ANY_PACKED_TYPE_TAG_BYTE_PREFIX) {
  const sourcemeta::jsontoolkit::JSON input =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/schemas/encoding/v1.json",
    "name": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "options": {}
  })JSON");

  const sourcemeta::jsonbinpack::Plan result{
      sourcemeta::jsonbinpack::parse(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::holds_alternative<ANY_PACKED_TYPE_TAG_BYTE_PREFIX>(result));
}
