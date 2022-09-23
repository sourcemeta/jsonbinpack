#include "encode_utils.h"
#include <algorithm>     // std::transform
#include <gtest/gtest.h> // EXPECT_EQ
#include <iterator>      // std::back_inserter

static auto to_byte(std::uint8_t input) -> std::byte {
  return std::byte{input};
}

auto OutputByteStream::bytes() const -> const std::vector<std::byte> {
  std::vector<std::byte> result{};
  const std::string string{this->str()};
  std::transform(string.cbegin(), string.cend(), std::back_inserter(result),
                 to_byte);
  return result;
}

auto EXPECT_BYTES(const OutputByteStream &stream,
                  std::initializer_list<std::uint8_t> bytes) -> void {
  const std::vector<std::byte> actual{stream.bytes()};
  std::vector<std::byte> expected{};
  std::transform(bytes.begin(), bytes.end(), std::back_inserter(expected),
                 to_byte);
  EXPECT_EQ(actual, expected);
}
