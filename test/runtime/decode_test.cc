#include <gtest/gtest.h>

#include "decode_utils.h"

#include <sourcemeta/jsonbinpack/runtime.h>
#include <sourcemeta/jsontoolkit/json.h>

TEST(JSONBinPack_Decoder, generic_decode_BOUNDED_MULTIPLE_8BITS_ENUM_FIXED) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream stream{0x00};
  Decoder decoder{stream};
  BOUNDED_MULTIPLE_8BITS_ENUM_FIXED options{-5, -1, 1};
  const auto result = decoder.read(options);
  const sourcemeta::jsontoolkit::JSON expected{-5};
  EXPECT_EQ(result, expected);
}
