#include <gtest/gtest.h>

#include <sourcemeta/jsonbinpack/runtime.h>
#include <sourcemeta/jsontoolkit/json.h>

TEST(JSONBinPack_Loader_v1, invalid_encoding_name) {
  const sourcemeta::jsontoolkit::JSON input =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "FOO_BAR",
    "binpackOptions": {}
  })JSON");

  EXPECT_THROW(sourcemeta::jsonbinpack::load(input),
               sourcemeta::jsonbinpack::EncodingError);
}
