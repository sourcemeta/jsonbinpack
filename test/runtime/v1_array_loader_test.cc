#include <gtest/gtest.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/jsonbinpack/runtime.h>

#include <variant>

TEST(JSONBinPack_Loader_v1, FIXED_TYPED_ARRAY_enum_integer_number) {
  const sourcemeta::core::JSON input = sourcemeta::core::parse_json(R"JSON({
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

  const auto result{sourcemeta::jsonbinpack::load(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::holds_alternative<FIXED_TYPED_ARRAY>(result));
  EXPECT_EQ(std::get<FIXED_TYPED_ARRAY>(result).size, 3);
  EXPECT_TRUE(std::holds_alternative<DOUBLE_VARINT_TUPLE>(
      *(std::get<FIXED_TYPED_ARRAY>(result).encoding)));
  EXPECT_EQ(std::get<FIXED_TYPED_ARRAY>(result).prefix_encodings.size(), 2);

  EXPECT_TRUE(std::holds_alternative<BYTE_CHOICE_INDEX>(
      std::get<FIXED_TYPED_ARRAY>(result).prefix_encodings.at(0)));
  EXPECT_EQ(std::get<BYTE_CHOICE_INDEX>(
                std::get<FIXED_TYPED_ARRAY>(result).prefix_encodings.at(0))
                .choices.size(),
            2);
  EXPECT_EQ(std::get<BYTE_CHOICE_INDEX>(
                std::get<FIXED_TYPED_ARRAY>(result).prefix_encodings.at(0))
                .choices.at(0),
            sourcemeta::core::JSON{1});
  EXPECT_EQ(std::get<BYTE_CHOICE_INDEX>(
                std::get<FIXED_TYPED_ARRAY>(result).prefix_encodings.at(0))
                .choices.at(1),
            sourcemeta::core::JSON{2});

  EXPECT_TRUE(std::holds_alternative<ARBITRARY_MULTIPLE_ZIGZAG_VARINT>(
      std::get<FIXED_TYPED_ARRAY>(result).prefix_encodings.at(1)));
  EXPECT_EQ(std::get<ARBITRARY_MULTIPLE_ZIGZAG_VARINT>(
                std::get<FIXED_TYPED_ARRAY>(result).prefix_encodings.at(1))
                .multiplier,
            1);
}

TEST(JSONBinPack_Loader_v1, BOUNDED_8BITS_TYPED_ARRAY_enum_integer_number) {
  const sourcemeta::core::JSON input = sourcemeta::core::parse_json(R"JSON({
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

  const auto result{sourcemeta::jsonbinpack::load(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::holds_alternative<BOUNDED_8BITS_TYPED_ARRAY>(result));
  EXPECT_EQ(std::get<BOUNDED_8BITS_TYPED_ARRAY>(result).minimum, 1);
  EXPECT_EQ(std::get<BOUNDED_8BITS_TYPED_ARRAY>(result).maximum, 3);
  EXPECT_TRUE(std::holds_alternative<DOUBLE_VARINT_TUPLE>(
      *(std::get<BOUNDED_8BITS_TYPED_ARRAY>(result).encoding)));
  EXPECT_EQ(std::get<BOUNDED_8BITS_TYPED_ARRAY>(result).prefix_encodings.size(),
            2);

  EXPECT_TRUE(std::holds_alternative<BYTE_CHOICE_INDEX>(
      std::get<BOUNDED_8BITS_TYPED_ARRAY>(result).prefix_encodings.at(0)));
  EXPECT_EQ(
      std::get<BYTE_CHOICE_INDEX>(
          std::get<BOUNDED_8BITS_TYPED_ARRAY>(result).prefix_encodings.at(0))
          .choices.size(),
      2);
  EXPECT_EQ(
      std::get<BYTE_CHOICE_INDEX>(
          std::get<BOUNDED_8BITS_TYPED_ARRAY>(result).prefix_encodings.at(0))
          .choices.at(0),
      sourcemeta::core::JSON{1});
  EXPECT_EQ(
      std::get<BYTE_CHOICE_INDEX>(
          std::get<BOUNDED_8BITS_TYPED_ARRAY>(result).prefix_encodings.at(0))
          .choices.at(1),
      sourcemeta::core::JSON{2});

  EXPECT_TRUE(std::holds_alternative<ARBITRARY_MULTIPLE_ZIGZAG_VARINT>(
      std::get<BOUNDED_8BITS_TYPED_ARRAY>(result).prefix_encodings.at(1)));
  EXPECT_EQ(
      std::get<ARBITRARY_MULTIPLE_ZIGZAG_VARINT>(
          std::get<BOUNDED_8BITS_TYPED_ARRAY>(result).prefix_encodings.at(1))
          .multiplier,
      1);
}

TEST(JSONBinPack_Loader_v1, FLOOR_TYPED_ARRAY_enum_integer_number) {
  const sourcemeta::core::JSON input = sourcemeta::core::parse_json(R"JSON({
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

  const auto result{sourcemeta::jsonbinpack::load(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::holds_alternative<FLOOR_TYPED_ARRAY>(result));
  EXPECT_EQ(std::get<FLOOR_TYPED_ARRAY>(result).minimum, 1);
  EXPECT_TRUE(std::holds_alternative<DOUBLE_VARINT_TUPLE>(
      *(std::get<FLOOR_TYPED_ARRAY>(result).encoding)));
  EXPECT_EQ(std::get<FLOOR_TYPED_ARRAY>(result).prefix_encodings.size(), 2);

  EXPECT_TRUE(std::holds_alternative<BYTE_CHOICE_INDEX>(
      std::get<FLOOR_TYPED_ARRAY>(result).prefix_encodings.at(0)));
  EXPECT_EQ(std::get<BYTE_CHOICE_INDEX>(
                std::get<FLOOR_TYPED_ARRAY>(result).prefix_encodings.at(0))
                .choices.size(),
            2);
  EXPECT_EQ(std::get<BYTE_CHOICE_INDEX>(
                std::get<FLOOR_TYPED_ARRAY>(result).prefix_encodings.at(0))
                .choices.at(0),
            sourcemeta::core::JSON{1});
  EXPECT_EQ(std::get<BYTE_CHOICE_INDEX>(
                std::get<FLOOR_TYPED_ARRAY>(result).prefix_encodings.at(0))
                .choices.at(1),
            sourcemeta::core::JSON{2});

  EXPECT_TRUE(std::holds_alternative<ARBITRARY_MULTIPLE_ZIGZAG_VARINT>(
      std::get<FLOOR_TYPED_ARRAY>(result).prefix_encodings.at(1)));
  EXPECT_EQ(std::get<ARBITRARY_MULTIPLE_ZIGZAG_VARINT>(
                std::get<FLOOR_TYPED_ARRAY>(result).prefix_encodings.at(1))
                .multiplier,
            1);
}

TEST(JSONBinPack_Loader_v1, ROOF_TYPED_ARRAY_enum_integer_number) {
  const sourcemeta::core::JSON input = sourcemeta::core::parse_json(R"JSON({
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

  const auto result{sourcemeta::jsonbinpack::load(input)};
  using namespace sourcemeta::jsonbinpack;
  EXPECT_TRUE(std::holds_alternative<ROOF_TYPED_ARRAY>(result));
  EXPECT_EQ(std::get<ROOF_TYPED_ARRAY>(result).maximum, 3);
  EXPECT_TRUE(std::holds_alternative<DOUBLE_VARINT_TUPLE>(
      *(std::get<ROOF_TYPED_ARRAY>(result).encoding)));
  EXPECT_EQ(std::get<ROOF_TYPED_ARRAY>(result).prefix_encodings.size(), 2);

  EXPECT_TRUE(std::holds_alternative<BYTE_CHOICE_INDEX>(
      std::get<ROOF_TYPED_ARRAY>(result).prefix_encodings.at(0)));
  EXPECT_EQ(std::get<BYTE_CHOICE_INDEX>(
                std::get<ROOF_TYPED_ARRAY>(result).prefix_encodings.at(0))
                .choices.size(),
            2);
  EXPECT_EQ(std::get<BYTE_CHOICE_INDEX>(
                std::get<ROOF_TYPED_ARRAY>(result).prefix_encodings.at(0))
                .choices.at(0),
            sourcemeta::core::JSON{1});
  EXPECT_EQ(std::get<BYTE_CHOICE_INDEX>(
                std::get<ROOF_TYPED_ARRAY>(result).prefix_encodings.at(0))
                .choices.at(1),
            sourcemeta::core::JSON{2});

  EXPECT_TRUE(std::holds_alternative<ARBITRARY_MULTIPLE_ZIGZAG_VARINT>(
      std::get<ROOF_TYPED_ARRAY>(result).prefix_encodings.at(1)));
  EXPECT_EQ(std::get<ARBITRARY_MULTIPLE_ZIGZAG_VARINT>(
                std::get<ROOF_TYPED_ARRAY>(result).prefix_encodings.at(1))
                .multiplier,
            1);
}
