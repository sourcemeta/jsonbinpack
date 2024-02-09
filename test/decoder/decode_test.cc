#include <gtest/gtest.h>

#include "decode_utils.h"

#include <sourcemeta/jsonbinpack/decoder.h>
#include <sourcemeta/jsontoolkit/json.h>

TEST(Decoder, generic_decode_BOUNDED_MULTIPLE_8BITS_ENUM_FIXED) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x00};
  Decoder decoder{stream};
  BOUNDED_MULTIPLE_8BITS_ENUM_FIXED options{-5, -1, 1};
  const sourcemeta::jsontoolkit::JSON result = decoder.decode(options);
  const sourcemeta::jsontoolkit::JSON expected{-5};
  EXPECT_EQ(result, expected);
}
