#include "encode_utils.h"
#include <gtest/gtest.h>
#include <jsonbinpack/encoder/integer_encoder.h>
#include <jsontoolkit/json.h>

TEST(Encoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__minus_5_minus_5_minus_1_1) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{-5};
  document.parse();
  OutputByteStream stream{};
  BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(stream, document, {-5, -1, 1});
  EXPECT_BYTES(stream, {0x00});
}

TEST(Encoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__2_minus_5_5_1) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{2};
  document.parse();
  OutputByteStream stream{};
  BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(stream, document, {-5, 5, 1});
  EXPECT_BYTES(stream, {0x07});
}

TEST(Encoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__5_2_8_1) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{5};
  document.parse();
  OutputByteStream stream{};
  BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(stream, document, {2, 8, 1});
  EXPECT_BYTES(stream, {0x03});
}

TEST(Encoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__5_1_19_5) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{5};
  document.parse();
  OutputByteStream stream{};
  BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(stream, document, {1, 19, 5});
  EXPECT_BYTES(stream, {0x00});
}

TEST(Encoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__15_1_19_5) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{15};
  document.parse();
  OutputByteStream stream{};
  BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(stream, document, {1, 19, 5});
  EXPECT_BYTES(stream, {0x02});
}

TEST(Encoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__255_0_255_1) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{255};
  document.parse();
  OutputByteStream stream{};
  BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(stream, document, {0, 255, 1});
  EXPECT_BYTES(stream, {0xff});
}

TEST(Encoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__5_2_8_minus_1) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{5};
  document.parse();
  OutputByteStream stream{};
  BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(stream, document, {2, 8, -1});
  EXPECT_BYTES(stream, {0x03});
}

TEST(Encoder, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED__5_1_19_minus_5) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{5};
  document.parse();
  OutputByteStream stream{};
  BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(stream, document, {1, 19, -5});
  EXPECT_BYTES(stream, {0x00});
}

TEST(Encoder, FLOOR_MULTIPLE_ENUM_VARINT__minus_3_minus_10_1) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{-3};
  document.parse();
  OutputByteStream stream{};
  FLOOR_MULTIPLE_ENUM_VARINT(stream, document, {-10, 1});
  EXPECT_BYTES(stream, {0x07});
}

TEST(Encoder, FLOOR_MULTIPLE_ENUM_VARINT__5_2_1) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{5};
  document.parse();
  OutputByteStream stream{};
  FLOOR_MULTIPLE_ENUM_VARINT(stream, document, {2, 1});
  EXPECT_BYTES(stream, {0x03});
}

TEST(Encoder, FLOOR_MULTIPLE_ENUM_VARINT__10_5_5) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{10};
  document.parse();
  OutputByteStream stream{};
  FLOOR_MULTIPLE_ENUM_VARINT(stream, document, {5, 5});
  EXPECT_BYTES(stream, {0x01});
}

TEST(Encoder, FLOOR_MULTIPLE_ENUM_VARINT__10_2_5) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{10};
  document.parse();
  OutputByteStream stream{};
  FLOOR_MULTIPLE_ENUM_VARINT(stream, document, {2, 5});
  EXPECT_BYTES(stream, {0x01});
}

TEST(Encoder, FLOOR_MULTIPLE_ENUM_VARINT__1000_minus_2_4) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{1000};
  document.parse();
  OutputByteStream stream{};
  FLOOR_MULTIPLE_ENUM_VARINT(stream, document, {-2, 4});
  EXPECT_BYTES(stream, {0xfa, 0x01});
}

TEST(Encoder, ROOF_MULTIPLE_MIRROR_ENUM_VARINT__minus_3_minus_2_1) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{-3};
  document.parse();
  OutputByteStream stream{};
  ROOF_MULTIPLE_MIRROR_ENUM_VARINT(stream, document, {-2, 1});
  EXPECT_BYTES(stream, {0x01});
}

TEST(Encoder, ROOF_MULTIPLE_MIRROR_ENUM_VARINT__8_10_1) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{8};
  document.parse();
  OutputByteStream stream{};
  ROOF_MULTIPLE_MIRROR_ENUM_VARINT(stream, document, {10, 1});
  EXPECT_BYTES(stream, {0x02});
}

TEST(Encoder, ROOF_MULTIPLE_MIRROR_ENUM_VARINT__minus_15_minus_5_minus_5) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{-15};
  document.parse();
  OutputByteStream stream{};
  ROOF_MULTIPLE_MIRROR_ENUM_VARINT(stream, document, {-5, -5});
  EXPECT_BYTES(stream, {0x02});
}

TEST(Encoder, ROOF_MULTIPLE_MIRROR_ENUM_VARINT__5_16_5) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{5};
  document.parse();
  OutputByteStream stream{};
  ROOF_MULTIPLE_MIRROR_ENUM_VARINT(stream, document, {16, 5});
  EXPECT_BYTES(stream, {0x02});
}

TEST(Encoder, ROOF_MULTIPLE_MIRROR_ENUM_VARINT__10_15_5) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{10};
  document.parse();
  OutputByteStream stream{};
  ROOF_MULTIPLE_MIRROR_ENUM_VARINT(stream, document, {15, 5});
  EXPECT_BYTES(stream, {0x01});
}

TEST(Encoder, ROOF_MULTIPLE_MIRROR_ENUM_VARINT__10_15_minus_5) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{10};
  document.parse();
  OutputByteStream stream{};
  ROOF_MULTIPLE_MIRROR_ENUM_VARINT(stream, document, {15, -5});
  EXPECT_BYTES(stream, {0x01});
}

TEST(Encoder, ARBITRARY_MULTIPLE_ZIGZAG_VARINT__minus_25200_1) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{-25200};
  document.parse();
  OutputByteStream stream{};
  ARBITRARY_MULTIPLE_ZIGZAG_VARINT(stream, document, {1});
  EXPECT_BYTES(stream, {0xdf, 0x89, 0x03});
}

TEST(Encoder, ARBITRARY_MULTIPLE_ZIGZAG_VARINT__10_5) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{10};
  document.parse();
  OutputByteStream stream{};
  ARBITRARY_MULTIPLE_ZIGZAG_VARINT(stream, document, {5});
  EXPECT_BYTES(stream, {0x04});
}

TEST(Encoder, ARBITRARY_MULTIPLE_ZIGZAG_VARINT__10_minus_5) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{10};
  document.parse();
  OutputByteStream stream{};
  ARBITRARY_MULTIPLE_ZIGZAG_VARINT(stream, document, {-5});
  EXPECT_BYTES(stream, {0x04});
}
