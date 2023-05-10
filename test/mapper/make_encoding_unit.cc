#include <jsonbinpack/mapper/encoding.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

TEST(MapperEncoding, make_encoding_1) {
  auto result{sourcemeta::jsontoolkit::make_object()};
  auto options{sourcemeta::jsontoolkit::make_object()};
  sourcemeta::jsontoolkit::assign(options, "foo",
                                  sourcemeta::jsontoolkit::from(1));
  sourcemeta::jsonbinpack::mapper::make_encoding(result, "FOO_BAR_BAZ",
                                                 options);
  EXPECT_TRUE(sourcemeta::jsontoolkit::is_object(result));
  EXPECT_TRUE(sourcemeta::jsontoolkit::defines(result, "$schema"));
  EXPECT_TRUE(sourcemeta::jsontoolkit::defines(result, "name"));
  EXPECT_TRUE(sourcemeta::jsontoolkit::defines(result, "options"));
  EXPECT_TRUE(sourcemeta::jsonbinpack::mapper::is_encoding(result));
}
