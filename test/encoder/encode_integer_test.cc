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
