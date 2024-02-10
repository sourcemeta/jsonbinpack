#ifndef SOURCEMETA_JSONBINPACK_TEST_ENCODER_UTILS_H_
#define SOURCEMETA_JSONBINPACK_TEST_ENCODER_UTILS_H_

#include <gtest/gtest.h>

#include <algorithm>        // std::transform
#include <cstddef>          // std::byte
#include <cstdint>          // std::uint8_t
#include <initializer_list> // std::initializer_list
#include <iterator>         // std::back_inserter
#include <sstream>          // std::basic_ostringstream
#include <string>           // std::basic_string
#include <vector>           // std::vector

static inline auto to_byte(const std::uint8_t input) -> std::byte {
  return std::byte{input};
}

template <typename CharT>
class OutputByteStream : public std::basic_ostringstream<CharT> {
public:
  // Convert the stream into an array of bytes
  auto bytes() const -> const std::vector<std::byte> {
    std::vector<std::byte> result{};
    const std::basic_string<CharT> string{this->str()};
    std::transform(string.cbegin(), string.cend(), std::back_inserter(result),
                   [](const auto character) {
                     return to_byte(static_cast<std::uint8_t>(character));
                   });
    return result;
  }
};

template <typename CharT>
auto EXPECT_BYTES(const OutputByteStream<CharT> &stream,
                  std::initializer_list<std::uint8_t> bytes) -> void {
  const std::vector<std::byte> actual{stream.bytes()};
  std::vector<std::byte> expected{};
  std::transform(bytes.begin(), bytes.end(), std::back_inserter(expected),
                 [](const auto character) {
                   return to_byte(static_cast<std::uint8_t>(character));
                 });
  EXPECT_EQ(actual, expected);
}

#endif
