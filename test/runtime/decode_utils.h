#ifndef SOURCEMETA_JSONBINPACK_TEST_RUNTIME_DECODE_UTILS_H_
#define SOURCEMETA_JSONBINPACK_TEST_RUNTIME_DECODE_UTILS_H_

#include <cstdint>          // std::uint8_t
#include <initializer_list> // std::initializer_list
#include <memory>           // std::allocator
#include <sstream> // std::basic_ostringstream, std::basic_istringstream
#include <string>  // std::char_traits, std::basic_string

template <typename CharT, typename Traits = std::char_traits<CharT>,
          typename Allocator = std::allocator<CharT>>
static auto bytes_to_string(std::initializer_list<std::uint8_t> bytes)
    -> std::basic_string<CharT, Traits> {
  std::basic_ostringstream<CharT, Traits, Allocator> output{};
  for (const auto byte : bytes) {
    output.put(static_cast<CharT>(byte));
  }
  return output.str();
}

template <typename CharT>
class InputByteStream : public std::basic_istringstream<CharT> {
public:
  InputByteStream(std::initializer_list<std::uint8_t> bytes)
      : std::basic_istringstream<CharT>{bytes_to_string<CharT>(bytes)} {}
};

#endif
