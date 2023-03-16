#include <jsonbinpack/encoding/encoding.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>

TEST(Encoding, is_encoding_false) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": -100,
    "maximum": 100
  })JSON")};

  EXPECT_FALSE(sourcemeta::jsonbinpack::encoding::is_encoding(schema));
}

TEST(Encoding, is_encoding_true) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v1.json",
    "type": "integer",
    "encoding": "BOUNDED_MULTIPLE_8BITS_ENUM_FIXED",
    "options": {
      "minimum": -100,
      "maximum": 100,
      "multiplier": 1
    }
  })JSON")};

  EXPECT_TRUE(sourcemeta::jsonbinpack::encoding::is_encoding(schema));
}

TEST(Encoding, is_encoding_invalid_version) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v99999.json",
    "type": "integer",
    "encoding": "BOUNDED_MULTIPLE_8BITS_ENUM_FIXED",
    "options": {
      "minimum": -100,
      "maximum": 100,
      "multiplier": 1
    }
  })JSON")};

  EXPECT_FALSE(sourcemeta::jsonbinpack::encoding::is_encoding(schema));
}

TEST(Encoding, is_encoding_no_data) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://www.jsonbinpack.org/schemas/encoding/v1.json"
  })JSON")};

  EXPECT_FALSE(sourcemeta::jsonbinpack::encoding::is_encoding(schema));
}
