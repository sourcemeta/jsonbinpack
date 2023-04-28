#include "decode_utils.h"
#include <jsonbinpack/decoder/decoder.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

TEST(Decoder, generic_decode_BOUNDED_MULTIPLE_8BITS_ENUM_FIXED) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{0x00};
  Decoder decoder{stream};
  options::BOUNDED_MULTIPLE_8BITS_ENUM_FIXED options{-5, -1, 1};
  const sourcemeta::jsontoolkit::JSON result{decoder.decode(options)};
  const sourcemeta::jsontoolkit::JSON expected{
      sourcemeta::jsontoolkit::from(-5)};
  EXPECT_EQ(result, expected);
}
