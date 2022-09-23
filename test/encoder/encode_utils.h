#ifndef SOURCEMETA_JSONBINPACK_TEST_ENCODER_UTILS_H_
#define SOURCEMETA_JSONBINPACK_TEST_ENCODER_UTILS_H_

#include <cstddef>          // std::byte
#include <cstdint>          // std::uint8_t
#include <initializer_list> // std::initializer_list
#include <sstream>          // std::basic_ostringstream
#include <vector>           // std::vector

using ByteType = char;
// The byte type must actually be 1 byte
static_assert(sizeof(ByteType) == 1);
class OutputByteStream : public std::basic_ostringstream<ByteType> {
public:
  // Convert the stream into an array of bytes
  auto bytes() const -> const std::vector<std::byte>;
};

auto EXPECT_BYTES(const OutputByteStream &stream,
                  std::initializer_list<std::uint8_t> bytes) -> void;

#endif
