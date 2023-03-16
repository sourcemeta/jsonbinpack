#ifndef SOURCEMETA_JSONBINPACK_ENCODER_CONTEXT_H_
#define SOURCEMETA_JSONBINPACK_ENCODER_CONTEXT_H_

#include <map>    // std::map
#include <string> // std::string

namespace sourcemeta::jsonbinpack::encoder {

class Context {
public:
  auto record(const std::string &value, const std::uint64_t offset) -> void;
  auto remove_oldest() -> void;
  auto has(const std::string &value) const -> bool;
  auto offset(const std::string &value) const -> std::uint64_t;

private:
  std::map<std::string, std::uint64_t> strings;
  // A mirror of the above map to be able to sort by offset.
  // While this means we need 2x the amount of memory to keep track
  // of strings, it allows us to efficiently put an upper bound
  // on the amount of memory being consumed by this class.
  std::map<std::uint64_t, std::string> offsets;
  std::uint64_t byte_size = 0;
};

} // namespace sourcemeta::jsonbinpack::encoder

#endif
