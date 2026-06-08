#include <cstddef> // std::byte
#include <gtest/gtest.h>
#include <vector> // std::vector

#include <sourcemeta/jsonbinpack/runtime.h>

#include <sourcemeta/core/io.h>
#include <sourcemeta/core/json.h>
TEST(JSONBinPack_Encoder,
     FIXED_TYPED_ARBITRARY_OBJECT__no_length_string__integer) {
  using namespace sourcemeta::jsonbinpack;
  const sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("{\"foo\":1,\"bar\":2}");
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.FIXED_TYPED_ARBITRARY_OBJECT(
      document, {2, std::make_shared<Encoding>(UTF8_STRING_NO_LENGTH{3}),
                 std::make_shared<Encoding>(
                     BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1})});

  // Deal with object property non-determinism
  if (document.as_object().cbegin()->first == "foo") {
    EXPECT_EQ(stream.bytes(),
              (std::vector<std::byte>{std::byte{0x66}, std::byte{0x6f},
                                      std::byte{0x6f}, std::byte{0x01},
                                      std::byte{0x62}, std::byte{0x61},
                                      std::byte{0x72}, std::byte{0x02}}));
  } else {
    EXPECT_EQ(stream.bytes(),
              (std::vector<std::byte>{std::byte{0x62}, std::byte{0x61},
                                      std::byte{0x72}, std::byte{0x02},
                                      std::byte{0x66}, std::byte{0x6f},
                                      std::byte{0x6f}, std::byte{0x01}}));
  }
}

TEST(JSONBinPack_Encoder,
     VARINT_TYPED_ARBITRARY_OBJECT__no_length_string__integer) {
  using namespace sourcemeta::jsonbinpack;
  const sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("{\"foo\":1,\"bar\":2}");
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.VARINT_TYPED_ARBITRARY_OBJECT(
      document, {std::make_shared<Encoding>(UTF8_STRING_NO_LENGTH{3}),
                 std::make_shared<Encoding>(
                     BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1})});

  // Deal with object property non-determinism
  if (document.as_object().cbegin()->first == "foo") {
    EXPECT_EQ(stream.bytes(),
              (std::vector<std::byte>{
                  std::byte{0x02}, std::byte{0x66}, std::byte{0x6f},
                  std::byte{0x6f}, std::byte{0x01}, std::byte{0x62},
                  std::byte{0x61}, std::byte{0x72}, std::byte{0x02}}));
  } else {
    EXPECT_EQ(stream.bytes(),
              (std::vector<std::byte>{
                  std::byte{0x02}, std::byte{0x62}, std::byte{0x61},
                  std::byte{0x72}, std::byte{0x02}, std::byte{0x66},
                  std::byte{0x6f}, std::byte{0x6f}, std::byte{0x01}}));
  }
}
