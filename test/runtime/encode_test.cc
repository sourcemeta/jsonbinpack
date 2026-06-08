#include <cstddef> // std::byte
#include <gtest/gtest.h>
#include <sourcemeta/core/io.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/jsonbinpack/runtime.h>
#include <vector> // std::vector

TEST(JSONBinPack_Encoder, generic_encode_BOUNDED_MULTIPLE_8BITS_ENUM_FIXED) {
  using namespace sourcemeta::jsonbinpack;
  const sourcemeta::core::JSON document{-5};
  sourcemeta::core::OutputByteStream stream{};
  Encoder encoder{stream};
  BOUNDED_MULTIPLE_8BITS_ENUM_FIXED options{-5, -1, 1};
  encoder.write(document, options);
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{std::byte{0x00}}));
}

TEST(JSONBinPack_Encoder, ANY_PACKED_TYPE_TAG_BYTE_PREFIX_many) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::OutputByteStream stream{};
  Encoder encoder{stream};
  ANY_PACKED_TYPE_TAG_BYTE_PREFIX options;
  encoder.write(sourcemeta::core::JSON{1}, options);
  encoder.write(sourcemeta::core::JSON{2}, options);
  encoder.write(sourcemeta::core::JSON{3}, options);
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0x15}, std::byte{0x1d},
                                    std::byte{0x25}}));
}
