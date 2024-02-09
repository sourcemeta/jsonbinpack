#include <jsonbinpack/parser/parser.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>
#include <variant>

TEST(Parser_v1, ANY_PACKED_TYPE_TAG_BYTE_PREFIX) {
  const sourcemeta::jsontoolkit::JSON input{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v1.json",
    "name": "ANY_PACKED_TYPE_TAG_BYTE_PREFIX",
    "options": {}
  })JSON")};

  const sourcemeta::jsonbinpack::Encoding result{
      sourcemeta::jsonbinpack::parse(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::holds_alternative<ANY_PACKED_TYPE_TAG_BYTE_PREFIX>(result));
}
