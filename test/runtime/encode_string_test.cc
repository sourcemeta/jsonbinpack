#include <gtest/gtest.h>

#include "encode_utils.h"
#include <sourcemeta/jsonbinpack/runtime.h>
#include <sourcemeta/jsontoolkit/json.h>

TEST(JSONBinPack_Encoder, UTF8_STRING_NO_LENGTH_foo_bar) {
  const sourcemeta::jsontoolkit::JSON document{"foo bar"};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.UTF8_STRING_NO_LENGTH(document, {7});
  EXPECT_BYTES(stream, {0x66, 0x6f, 0x6f, 0x20, 0x62, 0x61, 0x72});
}

TEST(JSONBinPack_Encoder, FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED_foo_3) {
  const sourcemeta::jsontoolkit::JSON document{"foo"};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED(document, {3});
  EXPECT_BYTES(stream, {0x01, 0x66, 0x6f, 0x6f});
}

TEST(JSONBinPack_Encoder, FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED_foo_0_foo_3) {
  const sourcemeta::jsontoolkit::JSON document{"foo"};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED(document, {0});
  encoder.FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED(document, {3});
  EXPECT_BYTES(stream, {0x04, 0x66, 0x6f, 0x6f, 0x00, 0x01, 0x05});
}

TEST(JSONBinPack_Encoder, ROOF_VARINT_PREFIX_UTF8_STRING_SHARED_foo_4) {
  const sourcemeta::jsontoolkit::JSON document{"foo"};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.ROOF_VARINT_PREFIX_UTF8_STRING_SHARED(document, {4});
  EXPECT_BYTES(stream, {0x02, 0x66, 0x6f, 0x6f});
}

TEST(JSONBinPack_Encoder, ROOF_VARINT_PREFIX_UTF8_STRING_SHARED_foo_3_foo_5) {
  const sourcemeta::jsontoolkit::JSON document{"foo"};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.ROOF_VARINT_PREFIX_UTF8_STRING_SHARED(document, {3});
  encoder.ROOF_VARINT_PREFIX_UTF8_STRING_SHARED(document, {5});
  EXPECT_BYTES(stream, {0x01, 0x66, 0x6f, 0x6f, 0x00, 0x03, 0x05});
}

TEST(JSONBinPack_Encoder, BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED_foo_3_5) {
  const sourcemeta::jsontoolkit::JSON document{"foo"};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED(document, {3, 5});
  EXPECT_BYTES(stream, {0x01, 0x66, 0x6f, 0x6f});
}

TEST(JSONBinPack_Encoder, BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED_foo_3_3) {
  const sourcemeta::jsontoolkit::JSON document{"foo"};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED(document, {3, 3});
  EXPECT_BYTES(stream, {0x01, 0x66, 0x6f, 0x6f});
}

TEST(JSONBinPack_Encoder,
     BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED_foo_0_6_foo_3_100) {
  const sourcemeta::jsontoolkit::JSON document{"foo"};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED(document, {0, 6});
  encoder.BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED(document, {3, 100});
  EXPECT_BYTES(stream, {0x04, 0x66, 0x6f, 0x6f, 0x00, 0x01, 0x05});
}

TEST(JSONBinPack_Encoder, RFC3339_DATE_INTEGER_TRIPLET_2014_10_01) {
  const sourcemeta::jsontoolkit::JSON document{"2014-10-01"};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.RFC3339_DATE_INTEGER_TRIPLET(document, {});
  EXPECT_BYTES(stream, {0xde, 0x07, 0x0a, 0x01});
}

TEST(JSONBinPack_Encoder, PREFIX_VARINT_LENGTH_STRING_SHARED_foo) {
  const sourcemeta::jsontoolkit::JSON document{"foo"};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.PREFIX_VARINT_LENGTH_STRING_SHARED(document, {});
  EXPECT_BYTES(stream, {
                           0x04,            // String length + 1
                           0x66, 0x6f, 0x6f // "foo"
                       });
}

TEST(JSONBinPack_Encoder, PREFIX_VARINT_LENGTH_STRING_SHARED_foo_foo_foo_foo) {
  const sourcemeta::jsontoolkit::JSON document{"foo"};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.PREFIX_VARINT_LENGTH_STRING_SHARED(document, {});
  encoder.PREFIX_VARINT_LENGTH_STRING_SHARED(document, {});
  encoder.PREFIX_VARINT_LENGTH_STRING_SHARED(document, {});
  encoder.PREFIX_VARINT_LENGTH_STRING_SHARED(document, {});

  EXPECT_BYTES(stream, {
                           0x04,             // String length + 1
                           0x66, 0x6f, 0x6f, // "foo"
                           0x00,             // Start of pointer
                           0x05, // Pointer (current = 5 - location = 0)
                           0x00, // Start of pointer
                           0x03, // Pointer (current = 7 - location = 3)
                           0x00, // Start of pointer
                           0x03  // Pointer (current = 9 - location = 3)
                       });
}

TEST(JSONBinPack_Encoder,
     PREFIX_VARINT_LENGTH_STRING_SHARED_non_key_foo_key_foo) {
  const sourcemeta::jsontoolkit::JSON document{"foo"};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED(document, {3});
  encoder.PREFIX_VARINT_LENGTH_STRING_SHARED(document, {});

  EXPECT_BYTES(stream, {
                           0x01,             // String length + 1 - 3
                           0x66, 0x6f, 0x6f, // "foo"
                           0x04,             // String length + 1
                           0x66, 0x6f, 0x6f  // "foo"
                       });
}

TEST(JSONBinPack_Encoder,
     PREFIX_VARINT_LENGTH_STRING_SHARED_key_foo_non_key_foo) {
  const sourcemeta::jsontoolkit::JSON document{"foo"};
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::Encoder encoder{stream};
  encoder.PREFIX_VARINT_LENGTH_STRING_SHARED(document, {});
  encoder.FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED(document, {3});

  EXPECT_BYTES(stream, {
                           0x04,             // String length + 1
                           0x66, 0x6f, 0x6f, // "foo"
                           0x00,             // Start of pointer
                           0x01,             // String length + 1 - 3
                           0x05              // Pointer (6 - 1 = 5)
                       });
}
