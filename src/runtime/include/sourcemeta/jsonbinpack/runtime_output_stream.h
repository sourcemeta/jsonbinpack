#ifndef SOURCEMETA_JSONBINPACK_RUNTIME_OUTPUT_STREAM_H_
#define SOURCEMETA_JSONBINPACK_RUNTIME_OUTPUT_STREAM_H_
#ifndef DOXYGEN

#include "runtime_export.h"

#include <sourcemeta/jsonbinpack/numeric.h>
#include <sourcemeta/jsontoolkit/json.h>

#include <sourcemeta/jsonbinpack/runtime_encoder_context.h>
#include <sourcemeta/jsonbinpack/runtime_varint.h>

#include <algorithm> // std::find_if
#include <cassert>   // assert
#include <cstdint>   // std::int8_t, std::uint8_t, std::int64_t
#include <ios>       // std::ios_base
#include <iterator>  // std::cbegin, std::cend, std::distance
#include <ostream>   // std::basic_ostream

namespace sourcemeta::jsonbinpack {

/// @ingroup runtime
class SOURCEMETA_JSONBINPACK_RUNTIME_EXPORT OutputStream {
public:
  OutputStream(
      std::basic_ostream<sourcemeta::jsontoolkit::JSON::Char,
                         sourcemeta::jsontoolkit::JSON::CharTraits> &output)
      : stream{output} {
    this->stream.exceptions(std::ios_base::badbit | std::ios_base::failbit |
                            std::ios_base::eofbit);
  }

  // Prevent copying, as this class is tied to a stream resource
  OutputStream(const OutputStream &) = delete;
  auto operator=(const OutputStream &) -> OutputStream & = delete;

  inline auto position() const noexcept -> std::uint64_t {
    return static_cast<std::uint64_t>(this->stream.tellp());
  }

  inline auto put_byte(const std::uint8_t byte) -> void {
    this->stream.put(static_cast<sourcemeta::jsontoolkit::JSON::Char>(byte));
  }

  inline auto put_bytes(const std::uint16_t bytes) -> void {
    this->stream.write(
        reinterpret_cast<const sourcemeta::jsontoolkit::JSON::Char *>(&bytes),
        sizeof bytes);
  }

  inline auto put_varint(const std::uint64_t value) -> void {
    varint_encode(this->stream, value);
  }

  inline auto put_varint_zigzag(const std::int64_t value) -> void {
    varint_encode(this->stream, zigzag_encode(value));
  }

  inline auto
  put_string_utf8(const sourcemeta::jsontoolkit::JSON::String &string,
                  const std::uint64_t length) -> void {
    assert(string.size() == length);
    // Do a manual for-loop based on the provided length instead of a range
    // loop based on the string value to avoid accidental overflows
    for (std::uint64_t index = 0; index < length; index++) {
      this->put_byte(static_cast<std::uint8_t>(string[index]));
    }
  }

  inline auto context() -> Context & { return this->context_; }

private:
  std::basic_ostream<sourcemeta::jsontoolkit::JSON::Char,
                     sourcemeta::jsontoolkit::JSON::CharTraits> &stream;
  Context context_;
};

} // namespace sourcemeta::jsonbinpack

#endif
#endif
