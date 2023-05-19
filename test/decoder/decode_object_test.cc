#include "decode_utils.h"
#include <jsonbinpack/decoder/decoder.h>
#include <jsonbinpack/encoding/wrap.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

TEST(Decoder, FIXED_TYPED_ARBITRARY_OBJECT__no_length_string__integer) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{
      0x66, 0x6f, 0x6f, // "foo"
      0x01,             // 1
      0x62, 0x61, 0x72, // "bar"
      0x02              // 2
  };
  Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{
      decoder.FIXED_TYPED_ARBITRARY_OBJECT(
          {2, wrap(UTF8_STRING_NO_LENGTH{3}),
           wrap(BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1})})};
  EXPECT_TRUE(sourcemeta::jsontoolkit::is_object(result));
  EXPECT_EQ(sourcemeta::jsontoolkit::size(result), 2);
  EXPECT_TRUE(sourcemeta::jsontoolkit::defines(result, "foo"));
  EXPECT_TRUE(sourcemeta::jsontoolkit::defines(result, "bar"));
  const auto &foo{sourcemeta::jsontoolkit::at(result, "foo")};
  const auto &bar{sourcemeta::jsontoolkit::at(result, "bar")};
  EXPECT_TRUE(sourcemeta::jsontoolkit::is_integer(foo));
  EXPECT_TRUE(sourcemeta::jsontoolkit::is_integer(bar));
  EXPECT_EQ(sourcemeta::jsontoolkit::to_integer(foo), 1);
  EXPECT_EQ(sourcemeta::jsontoolkit::to_integer(bar), 2);
}

TEST(Decoder, VARINT_TYPED_ARBITRARY_OBJECT__no_length_string__integer) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{
      0x02,             // length 2
      0x66, 0x6f, 0x6f, // "foo"
      0x01,             // 1
      0x62, 0x61, 0x72, // "bar"
      0x02              // 2
  };
  Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{
      decoder.VARINT_TYPED_ARBITRARY_OBJECT(
          {wrap(UTF8_STRING_NO_LENGTH{3}),
           wrap(BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1})})};
  EXPECT_TRUE(sourcemeta::jsontoolkit::is_object(result));
  EXPECT_EQ(sourcemeta::jsontoolkit::size(result), 2);
  EXPECT_TRUE(sourcemeta::jsontoolkit::defines(result, "foo"));
  EXPECT_TRUE(sourcemeta::jsontoolkit::defines(result, "bar"));
  const auto &foo{sourcemeta::jsontoolkit::at(result, "foo")};
  const auto &bar{sourcemeta::jsontoolkit::at(result, "bar")};
  EXPECT_TRUE(sourcemeta::jsontoolkit::is_integer(foo));
  EXPECT_TRUE(sourcemeta::jsontoolkit::is_integer(bar));
  EXPECT_EQ(sourcemeta::jsontoolkit::to_integer(foo), 1);
  EXPECT_EQ(sourcemeta::jsontoolkit::to_integer(bar), 2);
}
