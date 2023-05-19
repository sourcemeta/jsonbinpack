#include "encode_utils.h"
#include <jsonbinpack/encoder/encoder.h>
#include <jsonbinpack/encoding/wrap.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

TEST(Encoder, FIXED_TYPED_ARBITRARY_OBJECT__no_length_string__integer) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::parse("{\"foo\":1,\"bar\":2}")};
  OutputByteStream<char> stream{};

  Encoder encoder{stream};
  encoder.FIXED_TYPED_ARBITRARY_OBJECT(
      document, {2, wrap(UTF8_STRING_NO_LENGTH{3}),
                 wrap(BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1})});
  EXPECT_BYTES(stream, {
                           0x66, 0x6f, 0x6f, // "foo"
                           0x01,             // 1
                           0x62, 0x61, 0x72, // "bar"
                           0x02              // 2
                       });
}

TEST(Encoder, VARINT_TYPED_ARBITRARY_OBJECT__no_length_string__integer) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::jsontoolkit::JSON document{
      sourcemeta::jsontoolkit::parse("{\"foo\":1,\"bar\":2}")};
  OutputByteStream<char> stream{};

  Encoder encoder{stream};
  encoder.VARINT_TYPED_ARBITRARY_OBJECT(
      document, {wrap(UTF8_STRING_NO_LENGTH{3}),
                 wrap(BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{0, 10, 1})});
  EXPECT_BYTES(stream, {
                           0x02,             // length 2
                           0x66, 0x6f, 0x6f, // "foo"
                           0x01,             // 1
                           0x62, 0x61, 0x72, // "bar"
                           0x02              // 2
                       });
}
