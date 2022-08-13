#ifndef SOURCEMETA_JSONBINPACK_TEST_ENCODER_UTILS_H_
#define SOURCEMETA_JSONBINPACK_TEST_ENCODER_UTILS_H_

#include <algorithm>        // std::transform
#include <cstddef>          // std::byte
#include <cstdint>          // std::uint8_t
#include <gtest/gtest.h>    // EXPECT_EQ
#include <initializer_list> // std::initializer_list
#include <iterator>         // std::back_inserter
#include <sstream>          // std::basic_ostringstream
#include <string>           // std::basic_string
#include <vector>           // std::vector

static auto to_byte(std::uint8_t input) -> std::byte {
  return std::byte{input};
}

using ByteType = char;
// The byte type must actually be 1 byte
static_assert(sizeof(ByteType) == 1);
class OutputByteStream : public std::basic_ostringstream<ByteType> {
public:
  // Convert the stream into an array of bytes
  auto bytes() const -> const std::vector<std::byte> {
    std::vector<std::byte> result{};
    const std::string string{this->str()};
    std::transform(string.cbegin(), string.cend(), std::back_inserter(result),
                   to_byte);
    return result;
  }
};

auto EXPECT_BYTES(const OutputByteStream &stream,
                  std::initializer_list<std::uint8_t> bytes) -> void {
  const std::vector<std::byte> actual{stream.bytes()};
  std::vector<std::byte> expected{};
  std::transform(bytes.begin(), bytes.end(), std::back_inserter(expected),
                 to_byte);
  EXPECT_EQ(actual, expected);
}

#endif
