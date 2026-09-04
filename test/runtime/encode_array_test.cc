#include <cstddef> // std::byte
#include <vector>

#include <sourcemeta/jsonbinpack/runtime.h>

#include <sourcemeta/core/io.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/test.h>
TEST(FIXED_TYPED_ARRAY_0_1_2__no_prefix_encodings) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document = sourcemeta::core::parse_json("[ 0, 1, 2 ]");
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.FIXED_TYPED_ARRAY(
      document,
      {.size = 3,
       .encoding = std::make_shared<Encoding>(BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{
           .minimum = 0, .maximum = 10, .multiplier = 1}),
       .prefix_encodings = {}});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0x00}, std::byte{0x01},
                                    std::byte{0x02}}));
}

TEST(FIXED_TYPED_ARRAY_0_1_true__semityped) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("[ 0, 1, true ]");
  sourcemeta::core::OutputByteStream stream{};

  std::vector<sourcemeta::core::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  Encoding first{BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{
      .minimum = 0, .maximum = 10, .multiplier = 1}};
  Encoding second{BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{
      .minimum = 0, .maximum = 10, .multiplier = 1}};

  Encoder encoder{stream};
  encoder.FIXED_TYPED_ARRAY(
      document, {.size = 3,
                 .encoding = std::make_shared<Encoding>(
                     BYTE_CHOICE_INDEX{std::move(choices)}),
                 .prefix_encodings = {std::move(first), std::move(second)}});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0x00}, std::byte{0x01},
                                    std::byte{0x01}}));
}

TEST(FIXED_TYPED_ARRAY_empty__no_prefix_encodings) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document{sourcemeta::core::JSON::Array{}};
  sourcemeta::core::OutputByteStream stream{};

  Encoder encoder{stream};
  encoder.FIXED_TYPED_ARRAY(
      document,
      {.size = 0,
       .encoding = std::make_shared<Encoding>(BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{
           .minimum = 0, .maximum = 10, .multiplier = 1}),
       .prefix_encodings = {}});
  EXPECT_EQ(stream.bytes(), (std::vector<std::byte>{}));
}

TEST(BOUNDED_8BITS_TYPED_ARRAY_true_false_true__no_prefix_encodings) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("[ true, false, true ]");
  sourcemeta::core::OutputByteStream stream{};

  std::vector<sourcemeta::core::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  Encoder encoder{stream};
  encoder.BOUNDED_8BITS_TYPED_ARRAY(document,
                                    {.minimum = 0,
                                     .maximum = 3,
                                     .encoding = std::make_shared<Encoding>(
                                         BYTE_CHOICE_INDEX{std::move(choices)}),
                                     .prefix_encodings = {}});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0x03}, std::byte{0x01},
                                    std::byte{0x00}, std::byte{0x01}}));
}

TEST(BOUNDED_8BITS_TYPED_ARRAY_true_false_true__same_max_min) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("[ true, false, true ]");
  sourcemeta::core::OutputByteStream stream{};

  std::vector<sourcemeta::core::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  Encoder encoder{stream};
  encoder.BOUNDED_8BITS_TYPED_ARRAY(document,
                                    {.minimum = 3,
                                     .maximum = 3,
                                     .encoding = std::make_shared<Encoding>(
                                         BYTE_CHOICE_INDEX{std::move(choices)}),
                                     .prefix_encodings = {}});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0x00}, std::byte{0x01},
                                    std::byte{0x00}, std::byte{0x01}}));
}

TEST(BOUNDED_8BITS_TYPED_ARRAY_true_false_5__1_3) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("[ true, false, 5 ]");
  sourcemeta::core::OutputByteStream stream{};

  std::vector<sourcemeta::core::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  Encoder encoder{stream};
  encoder.BOUNDED_8BITS_TYPED_ARRAY(
      document,
      {.minimum = 1,
       .maximum = 3,
       .encoding = std::make_shared<Encoding>(BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{
           .minimum = 0, .maximum = 255, .multiplier = 1}),
       .prefix_encodings = {BYTE_CHOICE_INDEX{choices},
                            BYTE_CHOICE_INDEX{choices}}});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0x02}, std::byte{0x01},
                                    std::byte{0x00}, std::byte{0x05}}));
}

TEST(BOUNDED_8BITS_TYPED_ARRAY_complex) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("[ true, \"foo\", 1000 ]");
  sourcemeta::core::OutputByteStream stream{};

  std::vector<sourcemeta::core::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  Encoder encoder{stream};
  encoder.BOUNDED_8BITS_TYPED_ARRAY(
      document,
      {.minimum = 0,
       .maximum = 10,
       .encoding = std::make_shared<Encoding>(
           FLOOR_MULTIPLE_ENUM_VARINT{.minimum = -2, .multiplier = 4}),
       .prefix_encodings = {BYTE_CHOICE_INDEX{choices},
                            FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED{3}}});
  EXPECT_EQ(
      stream.bytes(),
      (std::vector<std::byte>{std::byte{0x03}, std::byte{0x01}, std::byte{0x01},
                              std::byte{0x66}, std::byte{0x6f}, std::byte{0x6f},
                              std::byte{0xfa}, std::byte{0x01}}));
}

TEST(FLOOR_TYPED_ARRAY_true_false_true__no_prefix_encodings) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("[ true, false, true ]");
  sourcemeta::core::OutputByteStream stream{};

  std::vector<sourcemeta::core::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  Encoder encoder{stream};
  encoder.FLOOR_TYPED_ARRAY(document,
                            {.minimum = 0,
                             .encoding = std::make_shared<Encoding>(
                                 BYTE_CHOICE_INDEX{std::move(choices)}),
                             .prefix_encodings = {}});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0x03}, std::byte{0x01},
                                    std::byte{0x00}, std::byte{0x01}}));
}

TEST(FLOOR_TYPED_ARRAY_true_false_5__1_3) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("[ true, false, 5 ]");
  sourcemeta::core::OutputByteStream stream{};

  std::vector<sourcemeta::core::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  Encoder encoder{stream};
  encoder.FLOOR_TYPED_ARRAY(
      document,
      {.minimum = 1,
       .encoding = std::make_shared<Encoding>(BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{
           .minimum = 0, .maximum = 255, .multiplier = 1}),
       .prefix_encodings = {BYTE_CHOICE_INDEX{choices},
                            BYTE_CHOICE_INDEX{choices}}});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0x02}, std::byte{0x01},
                                    std::byte{0x00}, std::byte{0x05}}));
}

TEST(FLOOR_TYPED_ARRAY_complex) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("[ true, \"foo\", 1000 ]");
  sourcemeta::core::OutputByteStream stream{};

  std::vector<sourcemeta::core::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  Encoder encoder{stream};
  encoder.FLOOR_TYPED_ARRAY(
      document,
      {.minimum = 0,
       .encoding = std::make_shared<Encoding>(
           FLOOR_MULTIPLE_ENUM_VARINT{.minimum = -2, .multiplier = 4}),
       .prefix_encodings = {BYTE_CHOICE_INDEX{choices},
                            FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED{3}}});
  EXPECT_EQ(
      stream.bytes(),
      (std::vector<std::byte>{std::byte{0x03}, std::byte{0x01}, std::byte{0x01},
                              std::byte{0x66}, std::byte{0x6f}, std::byte{0x6f},
                              std::byte{0xfa}, std::byte{0x01}}));
}

TEST(ROOF_TYPED_ARRAY_true_false_true__no_prefix_encodings) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("[ true, false, true ]");
  sourcemeta::core::OutputByteStream stream{};

  std::vector<sourcemeta::core::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  Encoder encoder{stream};
  encoder.ROOF_TYPED_ARRAY(document,
                           {.maximum = 6,
                            .encoding = std::make_shared<Encoding>(
                                BYTE_CHOICE_INDEX{std::move(choices)}),
                            .prefix_encodings = {}});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0x03}, std::byte{0x01},
                                    std::byte{0x00}, std::byte{0x01}}));
}

TEST(ROOF_TYPED_ARRAY_true_false_5__1_3) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("[ true, false, 5 ]");
  sourcemeta::core::OutputByteStream stream{};

  std::vector<sourcemeta::core::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  Encoder encoder{stream};
  encoder.ROOF_TYPED_ARRAY(
      document,
      {.maximum = 5,
       .encoding = std::make_shared<Encoding>(BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{
           .minimum = 0, .maximum = 255, .multiplier = 1}),
       .prefix_encodings = {BYTE_CHOICE_INDEX{choices},
                            BYTE_CHOICE_INDEX{choices}}});
  EXPECT_EQ(stream.bytes(),
            (std::vector<std::byte>{std::byte{0x02}, std::byte{0x01},
                                    std::byte{0x00}, std::byte{0x05}}));
}

TEST(ROOF_TYPED_ARRAY_complex) {
  using namespace sourcemeta::jsonbinpack;
  sourcemeta::core::JSON document =
      sourcemeta::core::parse_json("[ true, \"foo\", 1000 ]");
  sourcemeta::core::OutputByteStream stream{};

  std::vector<sourcemeta::core::JSON> choices;
  choices.emplace_back(false);
  choices.emplace_back(true);

  Encoder encoder{stream};
  encoder.ROOF_TYPED_ARRAY(
      document,
      {.maximum = 6,
       .encoding = std::make_shared<Encoding>(
           FLOOR_MULTIPLE_ENUM_VARINT{.minimum = -2, .multiplier = 4}),
       .prefix_encodings = {BYTE_CHOICE_INDEX{choices},
                            ROOF_VARINT_PREFIX_UTF8_STRING_SHARED{3}}});
  EXPECT_EQ(
      stream.bytes(),
      (std::vector<std::byte>{std::byte{0x03}, std::byte{0x01}, std::byte{0x01},
                              std::byte{0x66}, std::byte{0x6f}, std::byte{0x6f},
                              std::byte{0xfa}, std::byte{0x01}}));
}
