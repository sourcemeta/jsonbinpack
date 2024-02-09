#include <gtest/gtest.h>

#include <sourcemeta/jsonbinpack/parser.h>
#include <sourcemeta/jsontoolkit/json.h>

#include <variant>

TEST(Parser_v1, DOUBLE_VARINT_TUPLE) {
  const sourcemeta::jsontoolkit::JSON input =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://jsonbinpack.sourcemeta.com/schemas/encoding/v1.json",
    "name": "DOUBLE_VARINT_TUPLE",
    "options": {}
  })JSON");

  const sourcemeta::jsonbinpack::Encoding result{
      sourcemeta::jsonbinpack::parse(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::holds_alternative<DOUBLE_VARINT_TUPLE>(result));
}
