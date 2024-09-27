#include <gtest/gtest.h>

#include <sourcemeta/jsonbinpack/runtime.h>
#include <sourcemeta/jsontoolkit/json.h>

#include <variant>

TEST(JSONBinPack_Parser_v1, FIXED_TYPED_ARRAY_enum_integer_number) {
  const sourcemeta::jsontoolkit::JSON input =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "FIXED_TYPED_ARRAY",
    "binpackOptions": {
      "size": 3,
      "encoding": {
        "binpackEncoding": "DOUBLE_VARINT_TUPLE",
        "binpackOptions": {}
      },
      "prefixEncodings": [
        {
          "binpackEncoding": "BYTE_CHOICE_INDEX",
          "binpackOptions": {
            "choices": [ 1, 2 ]
          }
        },
        {
          "binpackEncoding": "ARBITRARY_MULTIPLE_ZIGZAG_VARINT",
          "binpackOptions": {
            "multiplier": 1
          }
        }
      ]
    }
  })JSON");

  const sourcemeta::jsonbinpack::Plan result{
      sourcemeta::jsonbinpack::parse(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::holds_alternative<FIXED_TYPED_ARRAY>(result));
  EXPECT_EQ(std::get<FIXED_TYPED_ARRAY>(result).size, 3);
  EXPECT_TRUE(std::holds_alternative<DOUBLE_VARINT_TUPLE>(
      std::get<FIXED_TYPED_ARRAY>(result).encoding->value));
  EXPECT_EQ(std::get<FIXED_TYPED_ARRAY>(result).prefix_encodings.size(), 2);

  EXPECT_TRUE(std::holds_alternative<BYTE_CHOICE_INDEX>(
      std::get<FIXED_TYPED_ARRAY>(result).prefix_encodings.at(0).value));
  EXPECT_EQ(
      std::get<BYTE_CHOICE_INDEX>(
          std::get<FIXED_TYPED_ARRAY>(result).prefix_encodings.at(0).value)
          .choices.size(),
      2);
  EXPECT_EQ(
      std::get<BYTE_CHOICE_INDEX>(
          std::get<FIXED_TYPED_ARRAY>(result).prefix_encodings.at(0).value)
          .choices.at(0),
      sourcemeta::jsontoolkit::JSON{1});
  EXPECT_EQ(
      std::get<BYTE_CHOICE_INDEX>(
          std::get<FIXED_TYPED_ARRAY>(result).prefix_encodings.at(0).value)
          .choices.at(1),
      sourcemeta::jsontoolkit::JSON{2});

  EXPECT_TRUE(std::holds_alternative<ARBITRARY_MULTIPLE_ZIGZAG_VARINT>(
      std::get<FIXED_TYPED_ARRAY>(result).prefix_encodings.at(1).value));
  EXPECT_EQ(
      std::get<ARBITRARY_MULTIPLE_ZIGZAG_VARINT>(
          std::get<FIXED_TYPED_ARRAY>(result).prefix_encodings.at(1).value)
          .multiplier,
      1);
}

TEST(JSONBinPack_Parser_v1, BOUNDED_8BITS_TYPED_ARRAY_enum_integer_number) {
  const sourcemeta::jsontoolkit::JSON input =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "BOUNDED_8BITS_TYPED_ARRAY",
    "binpackOptions": {
      "minimum": 1,
      "maximum": 3,
      "encoding": {
        "binpackEncoding": "DOUBLE_VARINT_TUPLE",
        "binpackOptions": {}
      },
      "prefixEncodings": [
        {
          "binpackEncoding": "BYTE_CHOICE_INDEX",
          "binpackOptions": {
            "choices": [ 1, 2 ]
          }
        },
        {
          "binpackEncoding": "ARBITRARY_MULTIPLE_ZIGZAG_VARINT",
          "binpackOptions": {
            "multiplier": 1
          }
        }
      ]
    }
  })JSON");

  const sourcemeta::jsonbinpack::Plan result{
      sourcemeta::jsonbinpack::parse(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::holds_alternative<BOUNDED_8BITS_TYPED_ARRAY>(result));
  EXPECT_EQ(std::get<BOUNDED_8BITS_TYPED_ARRAY>(result).minimum, 1);
  EXPECT_EQ(std::get<BOUNDED_8BITS_TYPED_ARRAY>(result).maximum, 3);
  EXPECT_TRUE(std::holds_alternative<DOUBLE_VARINT_TUPLE>(
      std::get<BOUNDED_8BITS_TYPED_ARRAY>(result).encoding->value));
  EXPECT_EQ(std::get<BOUNDED_8BITS_TYPED_ARRAY>(result).prefix_encodings.size(),
            2);

  EXPECT_TRUE(std::holds_alternative<BYTE_CHOICE_INDEX>(
      std::get<BOUNDED_8BITS_TYPED_ARRAY>(result)
          .prefix_encodings.at(0)
          .value));
  EXPECT_EQ(
      std::get<BYTE_CHOICE_INDEX>(std::get<BOUNDED_8BITS_TYPED_ARRAY>(result)
                                      .prefix_encodings.at(0)
                                      .value)
          .choices.size(),
      2);
  EXPECT_EQ(
      std::get<BYTE_CHOICE_INDEX>(std::get<BOUNDED_8BITS_TYPED_ARRAY>(result)
                                      .prefix_encodings.at(0)
                                      .value)
          .choices.at(0),
      sourcemeta::jsontoolkit::JSON{1});
  EXPECT_EQ(
      std::get<BYTE_CHOICE_INDEX>(std::get<BOUNDED_8BITS_TYPED_ARRAY>(result)
                                      .prefix_encodings.at(0)
                                      .value)
          .choices.at(1),
      sourcemeta::jsontoolkit::JSON{2});

  EXPECT_TRUE(std::holds_alternative<ARBITRARY_MULTIPLE_ZIGZAG_VARINT>(
      std::get<BOUNDED_8BITS_TYPED_ARRAY>(result)
          .prefix_encodings.at(1)
          .value));
  EXPECT_EQ(std::get<ARBITRARY_MULTIPLE_ZIGZAG_VARINT>(
                std::get<BOUNDED_8BITS_TYPED_ARRAY>(result)
                    .prefix_encodings.at(1)
                    .value)
                .multiplier,
            1);
}

TEST(JSONBinPack_Parser_v1, FLOOR_TYPED_ARRAY_enum_integer_number) {
  const sourcemeta::jsontoolkit::JSON input =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "FLOOR_TYPED_ARRAY",
    "binpackOptions": {
      "minimum": 1,
      "encoding": {
        "binpackEncoding": "DOUBLE_VARINT_TUPLE",
        "binpackOptions": {}
      },
      "prefixEncodings": [
        {
          "binpackEncoding": "BYTE_CHOICE_INDEX",
          "binpackOptions": {
            "choices": [ 1, 2 ]
          }
        },
        {
          "binpackEncoding": "ARBITRARY_MULTIPLE_ZIGZAG_VARINT",
          "binpackOptions": {
            "multiplier": 1
          }
        }
      ]
    }
  })JSON");

  const sourcemeta::jsonbinpack::Plan result{
      sourcemeta::jsonbinpack::parse(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::holds_alternative<FLOOR_TYPED_ARRAY>(result));
  EXPECT_EQ(std::get<FLOOR_TYPED_ARRAY>(result).minimum, 1);
  EXPECT_TRUE(std::holds_alternative<DOUBLE_VARINT_TUPLE>(
      std::get<FLOOR_TYPED_ARRAY>(result).encoding->value));
  EXPECT_EQ(std::get<FLOOR_TYPED_ARRAY>(result).prefix_encodings.size(), 2);

  EXPECT_TRUE(std::holds_alternative<BYTE_CHOICE_INDEX>(
      std::get<FLOOR_TYPED_ARRAY>(result).prefix_encodings.at(0).value));
  EXPECT_EQ(
      std::get<BYTE_CHOICE_INDEX>(
          std::get<FLOOR_TYPED_ARRAY>(result).prefix_encodings.at(0).value)
          .choices.size(),
      2);
  EXPECT_EQ(
      std::get<BYTE_CHOICE_INDEX>(
          std::get<FLOOR_TYPED_ARRAY>(result).prefix_encodings.at(0).value)
          .choices.at(0),
      sourcemeta::jsontoolkit::JSON{1});
  EXPECT_EQ(
      std::get<BYTE_CHOICE_INDEX>(
          std::get<FLOOR_TYPED_ARRAY>(result).prefix_encodings.at(0).value)
          .choices.at(1),
      sourcemeta::jsontoolkit::JSON{2});

  EXPECT_TRUE(std::holds_alternative<ARBITRARY_MULTIPLE_ZIGZAG_VARINT>(
      std::get<FLOOR_TYPED_ARRAY>(result).prefix_encodings.at(1).value));
  EXPECT_EQ(
      std::get<ARBITRARY_MULTIPLE_ZIGZAG_VARINT>(
          std::get<FLOOR_TYPED_ARRAY>(result).prefix_encodings.at(1).value)
          .multiplier,
      1);
}

TEST(JSONBinPack_Parser_v1, ROOF_TYPED_ARRAY_enum_integer_number) {
  const sourcemeta::jsontoolkit::JSON input =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "tag:sourcemeta.com,2024:jsonbinpack/encoding/v1",
    "binpackEncoding": "ROOF_TYPED_ARRAY",
    "binpackOptions": {
      "maximum": 3,
      "encoding": {
        "binpackEncoding": "DOUBLE_VARINT_TUPLE",
        "binpackOptions": {}
      },
      "prefixEncodings": [
        {
          "binpackEncoding": "BYTE_CHOICE_INDEX",
          "binpackOptions": {
            "choices": [ 1, 2 ]
          }
        },
        {
          "binpackEncoding": "ARBITRARY_MULTIPLE_ZIGZAG_VARINT",
          "binpackOptions": {
            "multiplier": 1
          }
        }
      ]
    }
  })JSON");

  const sourcemeta::jsonbinpack::Plan result{
      sourcemeta::jsonbinpack::parse(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::holds_alternative<ROOF_TYPED_ARRAY>(result));
  EXPECT_EQ(std::get<ROOF_TYPED_ARRAY>(result).maximum, 3);
  EXPECT_TRUE(std::holds_alternative<DOUBLE_VARINT_TUPLE>(
      std::get<ROOF_TYPED_ARRAY>(result).encoding->value));
  EXPECT_EQ(std::get<ROOF_TYPED_ARRAY>(result).prefix_encodings.size(), 2);

  EXPECT_TRUE(std::holds_alternative<BYTE_CHOICE_INDEX>(
      std::get<ROOF_TYPED_ARRAY>(result).prefix_encodings.at(0).value));
  EXPECT_EQ(std::get<BYTE_CHOICE_INDEX>(
                std::get<ROOF_TYPED_ARRAY>(result).prefix_encodings.at(0).value)
                .choices.size(),
            2);
  EXPECT_EQ(std::get<BYTE_CHOICE_INDEX>(
                std::get<ROOF_TYPED_ARRAY>(result).prefix_encodings.at(0).value)
                .choices.at(0),
            sourcemeta::jsontoolkit::JSON{1});
  EXPECT_EQ(std::get<BYTE_CHOICE_INDEX>(
                std::get<ROOF_TYPED_ARRAY>(result).prefix_encodings.at(0).value)
                .choices.at(1),
            sourcemeta::jsontoolkit::JSON{2});

  EXPECT_TRUE(std::holds_alternative<ARBITRARY_MULTIPLE_ZIGZAG_VARINT>(
      std::get<ROOF_TYPED_ARRAY>(result).prefix_encodings.at(1).value));
  EXPECT_EQ(std::get<ARBITRARY_MULTIPLE_ZIGZAG_VARINT>(
                std::get<ROOF_TYPED_ARRAY>(result).prefix_encodings.at(1).value)
                .multiplier,
            1);
}
