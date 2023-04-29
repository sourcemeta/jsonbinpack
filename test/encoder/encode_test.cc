#include "encode_utils.h"
#include <jsonbinpack/encoder/encoder.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

TEST(Encoder, generic_encode_BOUNDED_MULTIPLE_8BITS_ENUM_FIXED) {
  using namespace sourcemeta::jsonbinpack;
  const sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::from(-5)};
  OutputByteStream<char> stream{};
  Encoder encoder{stream};
  options::BOUNDED_MULTIPLE_8BITS_ENUM_FIXED options{-5, -1, 1};
  encoder.encode(document, options);
  EXPECT_BYTES(stream, {0x00});
}
