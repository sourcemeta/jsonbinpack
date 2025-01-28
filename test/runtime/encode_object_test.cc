#include <gtest/gtest.h>

#include <sourcemeta/jsonbinpack/runtime.h>

#include <sourcemeta/core/json.h>

#include "encode_utils.h"

TEST(JSONBinPack_Encoder,
     FIXED_TYPED_ARBITRARY_OBJECT__no_length_string__integer) {
  using namespace sourcemeta::jsonbinpack;
  const sourcemeta::core::JSON document =
      sourcemeta::core::parse("{\"foo\":1,\"bar\":2}");
  OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.FIXED_TYPED_ARBITRARY_OBJECT(
      document, {2, std::make_shared<Encoding>(UTF8_STRING_NO_LENGTH{3}),
                 std::make_shared<Encoding>(
                     BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1})});

  // Deal with object property non-determinism
  if (document.as_object().cbegin()->first == "foo") {
    EXPECT_BYTES(stream, {
                             0x66, 0x6f, 0x6f, // "foo"
                             0x01,             // 1
                             0x62, 0x61, 0x72, // "bar"
                             0x02              // 2
                         });
  } else {
    EXPECT_BYTES(stream, {
                             0x62, 0x61, 0x72, // "bar"
                             0x02,             // 2
                             0x66, 0x6f, 0x6f, // "foo"
                             0x01              // 1
                         });
  }
}

TEST(JSONBinPack_Encoder,
     VARINT_TYPED_ARBITRARY_OBJECT__no_length_string__integer) {
  using namespace sourcemeta::jsonbinpack;
  const sourcemeta::core::JSON document =
      sourcemeta::core::parse("{\"foo\":1,\"bar\":2}");
  OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.VARINT_TYPED_ARBITRARY_OBJECT(
      document, {std::make_shared<Encoding>(UTF8_STRING_NO_LENGTH{3}),
                 std::make_shared<Encoding>(
                     BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1})});

  // Deal with object property non-determinism
  if (document.as_object().cbegin()->first == "foo") {
    EXPECT_BYTES(stream, {
                             0x02,             // length 2
                             0x66, 0x6f, 0x6f, // "foo"
                             0x01,             // 1
                             0x62, 0x61, 0x72, // "bar"
                             0x02              // 2
                         });
  } else {
    EXPECT_BYTES(stream, {
                             0x02,             // length 2
                             0x62, 0x61, 0x72, // "bar"
                             0x02,             // 2
                             0x66, 0x6f, 0x6f, // "foo"
                             0x01              // 1
                         });
  }
}
