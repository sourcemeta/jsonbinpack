#include "encode_utils.h"
#include <jsonbinpack/encoder/enum_encoder.h>
#include <jsontoolkit/json.h>

#include <gtest/gtest.h>
#include <vector> // std::vector

TEST(Encoder, BYTE_CHOICE_INDEX_1__1_0_0) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{1};
  document.parse();
  OutputByteStream stream{};
  std::vector<sourcemeta::jsontoolkit::JSON<std::string>> choices{1, 0, 0};
  choices.at(0).parse();
  choices.at(1).parse();
  choices.at(2).parse();
  BYTE_CHOICE_INDEX(stream, document, {choices});
  EXPECT_BYTES(stream, {0x00});
}

TEST(Encoder, BYTE_CHOICE_INDEX_1__0_1_0) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{1};
  document.parse();
  OutputByteStream stream{};
  std::vector<sourcemeta::jsontoolkit::JSON<std::string>> choices{0, 1, 0};
  choices.at(0).parse();
  choices.at(1).parse();
  choices.at(2).parse();
  BYTE_CHOICE_INDEX(stream, document, {choices});
  EXPECT_BYTES(stream, {0x01});
}

TEST(Encoder, BYTE_CHOICE_INDEX_1__0_0_1) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{1};
  document.parse();
  OutputByteStream stream{};
  std::vector<sourcemeta::jsontoolkit::JSON<std::string>> choices{0, 0, 1};
  choices.at(0).parse();
  choices.at(1).parse();
  choices.at(2).parse();
  BYTE_CHOICE_INDEX(stream, document, {choices});
  EXPECT_BYTES(stream, {0x02});
}

TEST(Encoder, BYTE_CHOICE_INDEX_bar__foo_bar_bar) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{"\"bar\""};
  document.parse();
  OutputByteStream stream{};
  std::vector<sourcemeta::jsontoolkit::JSON<std::string>> choices{
      "\"foo\"", "\"bar\"", "\"bar\""};
  choices.at(0).parse();
  choices.at(1).parse();
  choices.at(2).parse();
  BYTE_CHOICE_INDEX(stream, document, {choices});
  EXPECT_BYTES(stream, {0x01});
}

TEST(Encoder, BYTE_CHOICE_INDEX_non_scalar_1) {
  using namespace sourcemeta::jsonbinpack::encoder;
  sourcemeta::jsontoolkit::JSON<std::string> document{"{ \"foo\": 1 }"};
  document.parse();
  OutputByteStream stream{};

  sourcemeta::jsontoolkit::JSON<std::string> choice1("{ \"foo\": 2 }");
  sourcemeta::jsontoolkit::JSON<std::string> choice2("{}");
  sourcemeta::jsontoolkit::JSON<std::string> choice3("[ 1, 2, 3 ]");
  sourcemeta::jsontoolkit::JSON<std::string> choice4("{ \"foo\": 1 }");
  sourcemeta::jsontoolkit::JSON<std::string> choice5("{ \"bar\": 1 }");

  choice1.parse();
  choice2.parse();
  choice3.parse();
  choice4.parse();
  choice5.parse();

  std::vector<sourcemeta::jsontoolkit::JSON<std::string>> choices;
  choices.push_back(choice1);
  choices.push_back(choice2);
  choices.push_back(choice3);
  choices.push_back(choice4);
  choices.push_back(choice5);

  BYTE_CHOICE_INDEX(stream, document, {choices});
  EXPECT_BYTES(stream, {0x03});
}
