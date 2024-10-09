#include <gtest/gtest.h>

#include "encode_utils.h"
#include <sourcemeta/jsonbinpack/runtime.h>
#include <sourcemeta/jsontoolkit/json.h>

TEST(JSONBinPack_Encoder, generic_encode_BOUNDED_MULTIPLE_8BITS_ENUM_FIXED) {
  using namespace sourcemeta::jsonbinpack;
  const sourcemeta::jsontoolkit::JSON document{-5};
  OutputByteStream stream{};
  Encoder encoder{stream};
  BOUNDED_MULTIPLE_8BITS_ENUM_FIXED options{-5, -1, 1};
  encoder.write(document, options);
  EXPECT_BYTES(stream, {0x00});
}

TEST(JSONBinPack_Encoder, ANY_PACKED_TYPE_TAG_BYTE_PREFIX_many) {
  using namespace sourcemeta::jsonbinpack;
  OutputByteStream stream{};
  Encoder encoder{stream};
  ANY_PACKED_TYPE_TAG_BYTE_PREFIX options;
  encoder.write(sourcemeta::jsontoolkit::JSON{1}, options);
  encoder.write(sourcemeta::jsontoolkit::JSON{2}, options);
  encoder.write(sourcemeta::jsontoolkit::JSON{3}, options);
  EXPECT_BYTES(stream, {0x15, 0x1d, 0x25});
}
