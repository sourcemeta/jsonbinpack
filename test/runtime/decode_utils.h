#ifndef SOURCEMETA_JSONBINPACK_TEST_RUNTIME_DECODE_UTILS_H_
#define SOURCEMETA_JSONBINPACK_TEST_RUNTIME_DECODE_UTILS_H_

#include <sourcemeta/jsontoolkit/json.h>

#include <cstdint>          // std::uint8_t
#include <initializer_list> // std::initializer_list
#include <sstream> // std::basic_ostringstream, std::basic_istringstream

static auto bytes_to_string(std::initializer_list<std::uint8_t> bytes)
    -> sourcemeta::jsontoolkit::JSON::String {
  std::basic_ostringstream<sourcemeta::jsontoolkit::JSON::Char,
                           sourcemeta::jsontoolkit::JSON::CharTraits>
      output{};
  for (const auto byte : bytes) {
    output.put(static_cast<sourcemeta::jsontoolkit::JSON::Char>(byte));
  }
  return output.str();
}

class InputByteStream
    : public std::basic_istringstream<sourcemeta::jsontoolkit::JSON::Char> {
public:
  InputByteStream(std::initializer_list<std::uint8_t> bytes)
      : std::basic_istringstream<sourcemeta::jsontoolkit::JSON::Char>{
            bytes_to_string(bytes)} {}
};

#endif
