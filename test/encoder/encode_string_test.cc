#include "encode_utils.h"
#include <jsonbinpack/encoder/context.h>
#include <jsonbinpack/encoder/string_encoder.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

TEST(Encoder, UTF8_STRING_NO_LENGTH_foo_bar) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"foo bar\""};
  document.parse();
  OutputByteStream stream{};
  UTF8_STRING_NO_LENGTH(stream, document, {document.size()});
  EXPECT_BYTES(stream, {0x66, 0x6f, 0x6f, 0x20, 0x62, 0x61, 0x72});
}

TEST(Encoder, FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED_foo_3) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"foo\""};
  document.parse();
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::encoder::Context<std::string,
                                            typename OutputByteStream::pos_type>
      context;
  FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED(stream, document, {3}, context);
  EXPECT_BYTES(stream, {0x01, 0x66, 0x6f, 0x6f});
}

TEST(Encoder, FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED_foo_0_foo_3) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"foo\""};
  document.parse();
  OutputByteStream stream{};
  sourcemeta::jsonbinpack::encoder::Context<std::string,
                                            typename OutputByteStream::pos_type>
      context;
  FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED(stream, document, {0}, context);
  EXPECT_TRUE(context.has("foo"));
  FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED(stream, document, {3}, context);
  EXPECT_BYTES(stream, {0x04, 0x66, 0x6f, 0x6f, 0x00, 0x01, 0x05});
}
