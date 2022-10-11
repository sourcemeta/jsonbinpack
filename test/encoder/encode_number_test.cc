#include "encode_utils.h"
#include <jsonbinpack/encoder/number_encoder.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

TEST(Encoder, DOUBLE_VARINT_TUPLE_5) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{5.0};
  document.parse();
  OutputByteStream stream{};
  DOUBLE_VARINT_TUPLE(stream, document);
  EXPECT_BYTES(stream, {0x0a, 0x00});
}

TEST(Encoder, DOUBLE_VARINT_TUPLE_minus_3_point_14) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{-3.14};
  document.parse();
  OutputByteStream stream{};
  DOUBLE_VARINT_TUPLE(stream, document);
  EXPECT_BYTES(stream, {0xf3, 0x04, 0x02});
}

TEST(Encoder, DOUBLE_VARINT_TUPLE_minus_5) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{-5.0};
  document.parse();
  OutputByteStream stream{};
  DOUBLE_VARINT_TUPLE(stream, document);
  EXPECT_BYTES(stream, {0x09, 0x00});
}

TEST(Encoder, DOUBLE_VARINT_TUPLE_zero) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{0.0};
  document.parse();
  OutputByteStream stream{};
  DOUBLE_VARINT_TUPLE(stream, document);
  EXPECT_BYTES(stream, {0x00, 0x00});
}

TEST(Encoder, DOUBLE_VARINT_TUPLE_1235) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{1235.0};
  document.parse();
  OutputByteStream stream{};
  DOUBLE_VARINT_TUPLE(stream, document);
  EXPECT_BYTES(stream, {0xa6, 0x13, 0x00});
}

TEST(Encoder, DOUBLE_VARINT_TUPLE_0_point_1235) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{0.1235};
  document.parse();
  OutputByteStream stream{};
  DOUBLE_VARINT_TUPLE(stream, document);
  EXPECT_BYTES(stream, {0xa6, 0x13, 0x04});
}

TEST(Encoder, DOUBLE_VARINT_TUPLE_1_point_235) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{1.235};
  document.parse();
  OutputByteStream stream{};
  DOUBLE_VARINT_TUPLE(stream, document);
  EXPECT_BYTES(stream, {0xa6, 0x13, 0x03});
}

TEST(Encoder, DOUBLE_VARINT_TUPLE_0_point_01235) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{0.01235};
  document.parse();
  OutputByteStream stream{};
  DOUBLE_VARINT_TUPLE(stream, document);
  EXPECT_BYTES(stream, {0xa6, 0x13, 0x05});
}

TEST(Encoder, DOUBLE_VARINT_TUPLE_12_35) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{12.35};
  document.parse();
  OutputByteStream stream{};
  DOUBLE_VARINT_TUPLE(stream, document);
  EXPECT_BYTES(stream, {0xa6, 0x13, 0x02});
}

TEST(Encoder, DOUBLE_VARINT_TUPLE_0_point_001235) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{0.001235};
  document.parse();
  OutputByteStream stream{};
  DOUBLE_VARINT_TUPLE(stream, document);
  EXPECT_BYTES(stream, {0xa6, 0x13, 0x06});
}

TEST(Encoder, DOUBLE_VARINT_TUPLE_123_point_5) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{123.5};
  document.parse();
  OutputByteStream stream{};
  DOUBLE_VARINT_TUPLE(stream, document);
  EXPECT_BYTES(stream, {0xa6, 0x13, 0x01});
}

TEST(Encoder, DOUBLE_VARINT_TUPLE_314) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{314.0};
  document.parse();
  OutputByteStream stream{};
  DOUBLE_VARINT_TUPLE(stream, document);
  EXPECT_BYTES(stream, {0xf4, 0x04, 0x00});
}

TEST(Encoder, DOUBLE_VARINT_TUPLE_0_point_314) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{0.314};
  document.parse();
  OutputByteStream stream{};
  DOUBLE_VARINT_TUPLE(stream, document);
  EXPECT_BYTES(stream, {0xf4, 0x04, 0x03});
}

TEST(Encoder, DOUBLE_VARINT_TUPLE_3_point_14) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{3.14};
  document.parse();
  OutputByteStream stream{};
  DOUBLE_VARINT_TUPLE(stream, document);
  EXPECT_BYTES(stream, {0xf4, 0x04, 0x02});
}

TEST(Encoder, DOUBLE_VARINT_TUPLE_0_point_0314) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{0.0314};
  document.parse();
  OutputByteStream stream{};
  DOUBLE_VARINT_TUPLE(stream, document);
  EXPECT_BYTES(stream, {0xf4, 0x04, 0x04});
}

TEST(Encoder, DOUBLE_VARINT_TUPLE_31_point_4) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{31.4};
  document.parse();
  OutputByteStream stream{};
  DOUBLE_VARINT_TUPLE(stream, document);
  EXPECT_BYTES(stream, {0xf4, 0x04, 0x01});
}
