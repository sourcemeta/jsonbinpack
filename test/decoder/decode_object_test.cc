#include <gtest/gtest.h>

#include "decode_utils.h"

#include <sourcemeta/jsonbinpack/decoder.h>
#include <sourcemeta/jsonbinpack/encoding_wrap.h>
#include <sourcemeta/jsontoolkit/json.h>

TEST(Decoder, FIXED_TYPED_ARBITRARY_OBJECT__no_length_string__integer) {
  using namespace sourcemeta::jsonbinpack;
  InputByteStream<char> stream{
      0x66, 0x6f, 0x6f, // "foo"
      0x01,             // 1
      0x62, 0x61, 0x72, // "bar"
      0x02              // 2
  };
  Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result =
      decoder.FIXED_TYPED_ARBITRARY_OBJECT(
          {2, wrap(UTF8_STRING_NO_LENGTH{3}),
           wrap(BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1})});
  EXPECT_TRUE(result.is_object());
  EXPECT_EQ(result.size(), 2);
  EXPECT_TRUE(result.defines("foo"));
  EXPECT_TRUE(result.defines("bar"));
  const auto &foo{result.at("foo")};
  const auto &bar{result.at("bar")};
  EXPECT_TRUE(foo.is_integer());
  EXPECT_TRUE(bar.is_integer());
  EXPECT_EQ(foo.to_integer(), 1);
  EXPECT_EQ(bar.to_integer(), 2);
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
  const sourcemeta::jsontoolkit::JSON result =
      decoder.VARINT_TYPED_ARBITRARY_OBJECT(
          {wrap(UTF8_STRING_NO_LENGTH{3}),
           wrap(BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1})});
  EXPECT_TRUE(result.is_object());
  EXPECT_EQ(result.size(), 2);
  EXPECT_TRUE(result.defines("foo"));
  EXPECT_TRUE(result.defines("bar"));
  const auto &foo{result.at("foo")};
  const auto &bar{result.at("bar")};
  EXPECT_TRUE(foo.is_integer());
  EXPECT_TRUE(bar.is_integer());
  EXPECT_EQ(foo.to_integer(), 1);
  EXPECT_EQ(bar.to_integer(), 2);
}
