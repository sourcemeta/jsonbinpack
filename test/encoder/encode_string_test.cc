#include "encode_utils.h"
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
