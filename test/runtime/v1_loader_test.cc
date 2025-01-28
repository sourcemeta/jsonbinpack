#include <gtest/gtest.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/jsonbinpack/runtime.h>

TEST(JSONBinPack_Loader_v1, invalid_encoding_name) {
  const sourcemeta::core::JSON input = sourcemeta::core::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "FOO_BAR",
    "binpackOptions": {}
  })JSON");

  EXPECT_THROW(sourcemeta::jsonbinpack::load(input),
               sourcemeta::jsonbinpack::EncodingError);
}
