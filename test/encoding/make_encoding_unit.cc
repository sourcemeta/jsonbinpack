#include <jsonbinpack/encoding/encoding.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

TEST(Encoding, make_encoding_1) {
  auto result{sourcemeta::jsontoolkit::make_object()};
  auto options{sourcemeta::jsontoolkit::make_object()};
  sourcemeta::jsontoolkit::assign(options, "foo",
                                  sourcemeta::jsontoolkit::from(1));
  sourcemeta::jsonbinpack::encoding::make_encoding(
      result, sourcemeta::jsonbinpack::encoding::Type::Integer, "FOO_BAR_BAZ",
      options);
  EXPECT_TRUE(sourcemeta::jsontoolkit::is_object(result));
  EXPECT_TRUE(sourcemeta::jsontoolkit::defines(result, "$schema"));
  EXPECT_TRUE(sourcemeta::jsontoolkit::defines(result, "type"));
  EXPECT_TRUE(sourcemeta::jsontoolkit::defines(result, "encoding"));
  EXPECT_TRUE(sourcemeta::jsontoolkit::defines(result, "options"));
  EXPECT_TRUE(sourcemeta::jsonbinpack::encoding::is_encoding(result));
}

TEST(Encoding, make_integer_encoding_1) {
  auto result{sourcemeta::jsontoolkit::make_object()};
  auto options{sourcemeta::jsontoolkit::make_object()};
  sourcemeta::jsontoolkit::assign(options, "foo",
                                  sourcemeta::jsontoolkit::from(1));
  sourcemeta::jsonbinpack::encoding::make_integer_encoding(
      result, "FOO_BAR_BAZ", options);
  EXPECT_TRUE(sourcemeta::jsontoolkit::is_object(result));
  EXPECT_TRUE(sourcemeta::jsonbinpack::encoding::is_encoding(result));
  EXPECT_TRUE(sourcemeta::jsontoolkit::defines(result, "type"));
  EXPECT_EQ(sourcemeta::jsontoolkit::to_string(
                sourcemeta::jsontoolkit::at(result, "type")),
            "integer");
}