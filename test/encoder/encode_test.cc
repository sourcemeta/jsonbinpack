#include <gtest/gtest.h>

#include "encode_utils.h"
#include <sourcemeta/jsonbinpack/encoder.h>
#include <sourcemeta/jsontoolkit/json.h>

TEST(Encoder, generic_encode_BOUNDED_MULTIPLE_8BITS_ENUM_FIXED) {
  using namespace sourcemeta::jsonbinpack;
  const sourcemeta::jsontoolkit::JSON document{-5};
  OutputByteStream<char> stream{};
  Encoder encoder{stream};
  BOUNDED_MULTIPLE_8BITS_ENUM_FIXED options{-5, -1, 1};
  encoder.encode(document, options);
  EXPECT_BYTES(stream, {0x00});
}
