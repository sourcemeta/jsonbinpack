#include "decode_utils.h"
#include <jsonbinpack/decoder/string_decoder.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

TEST(Decoder, UTF8_STRING_NO_LENGTH_foo_bar) {
  using namespace sourcemeta::jsonbinpack::decoder;
  InputByteStream stream{0x66, 0x6f, 0x6f, 0x20, 0x62, 0x61, 0x72};
  sourcemeta::jsontoolkit::JSON<std::string> result{
      UTF8_STRING_NO_LENGTH<std::string>(stream, {7})};
  sourcemeta::jsontoolkit::JSON<std::string> expected{"\"foo bar\""};
  result.parse();
  expected.parse();
  EXPECT_EQ(result, expected);
}
