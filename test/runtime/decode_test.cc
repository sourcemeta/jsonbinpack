#include <gtest/gtest.h>

#include "decode_utils.h"

#include <sourcemeta/core/json.h>
#include <sourcemeta/jsonbinpack/runtime.h>

TEST(JSONBinPack_Decoder, generic_decode_BOUNDED_MULTIPLE_8BITS_ENUM_FIXED) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream stream{0x00};
  Decoder decoder{stream};
  BOUNDED_MULTIPLE_8BITS_ENUM_FIXED options{-5, -1, 1};
  const auto result = decoder.read(options);
  const sourcemeta::core::JSON expected{-5};
  EXPECT_EQ(result, expected);
}

TEST(JSONBinPack_Decoder, ANY_PACKED_TYPE_TAG_BYTE_PREFIX_many) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream stream{0x15, 0x1d, 0x25};
  Decoder decoder{stream};
  ANY_PACKED_TYPE_TAG_BYTE_PREFIX options;
  const auto result_1 = decoder.read(options);
  const auto result_2 = decoder.read(options);
  const auto result_3 = decoder.read(options);
  const sourcemeta::core::JSON expected_1{1};
  const sourcemeta::core::JSON expected_2{2};
  const sourcemeta::core::JSON expected_3{3};
  EXPECT_EQ(result_1, expected_1);
  EXPECT_EQ(result_2, expected_2);
  EXPECT_EQ(result_3, expected_3);
}
