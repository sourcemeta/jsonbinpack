#ifndef SOURCEMETA_JSONBINPACK_RUNTIME_ENCODER_CONTEXT_H_
#define SOURCEMETA_JSONBINPACK_RUNTIME_ENCODER_CONTEXT_H_
#ifndef DOXYGEN

#include "runtime_export.h"

#include <sourcemeta/jsontoolkit/json.h>

#include <cassert>  // assert
#include <iterator> // std::cbegin, std::cend
#include <map>      // std::map
#include <optional> // std::optional, std::nullopt
#include <utility>  // std::pair, std::make_pair

// Encoding a shared string has some overhead, such as the
// shared string marker + the offset, so its not worth
// doing for strings that are too small.
static constexpr auto MINIMUM_STRING_LENGTH{3};

// We don't want to allow the context to grow
// forever, otherwise an attacker could force the
// program to exhaust memory given an input
// document that contains a high number of large strings.
static constexpr auto MAXIMUM_BYTE_SIZE{20971520};

namespace sourcemeta::jsonbinpack {

class SOURCEMETA_JSONBINPACK_RUNTIME_EXPORT Context {
public:
  enum class Type { Standalone, PrefixLengthVarintPlusOne };

  auto record(const sourcemeta::jsontoolkit::JSON::String &value,
              const std::uint64_t offset, const Type type) -> void {
    const auto value_size{value.size()};
    if (value_size < MINIMUM_STRING_LENGTH) {
      return;
      // The value is too big for the context to start with
    } else if (value_size >= MAXIMUM_BYTE_SIZE) {
      return;
    }

    // Remove the oldest entries to make space if needed
    while (!this->strings.empty() &&
           this->byte_size + value_size >= MAXIMUM_BYTE_SIZE) {
      this->remove_oldest();
    }

    // If the string already exists, we want to
    // bump the offset for locality purposes.
    const auto maybe_entry{this->find(value, type)};
    if (maybe_entry.has_value()) {
      const auto key{std::make_pair(value, type)};
      const auto previous_offset{this->strings[key]};
      if (offset > previous_offset) {
        this->strings[key] = offset;
        this->offsets.erase(previous_offset);
        this->offsets.insert({offset, std::make_pair(value, type)});
      }
    } else {
      const auto result{
          this->offsets.insert({offset, std::make_pair(value, type)})};
      // Prevent recording two strings to the same offset
      assert(result.second);
      if (result.second) {
        this->strings.insert({std::make_pair(value, type), offset});
        this->byte_size += value_size;
      }
    }
  }

  auto remove_oldest() -> void {
    assert(!this->strings.empty());
    // std::map are by definition ordered by key,
    // so the begin iterator points to the entry
    // with the lowest offset, a.k.a. the oldest.
    const auto iterator{std::cbegin(this->offsets)};
    this->strings.erase(
        std::make_pair(iterator->second.first, iterator->second.second));
    this->byte_size -= iterator->second.first.size();
    this->offsets.erase(iterator);
  }

  auto find(const sourcemeta::jsontoolkit::JSON::String &value,
            const Type type) const -> std::optional<std::uint64_t> {
    const auto result{this->strings.find(std::make_pair(value, type))};
    if (result == this->strings.cend()) {
      return std::nullopt;
    }

    return result->second;
  }

private:
// Exporting symbols that depends on the standard C++ library is considered
// safe.
// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4275?view=msvc-170&redirectedfrom=MSDN
#if defined(_MSC_VER)
#pragma warning(disable : 4251 4275)
#endif
  // TODO: Keep a reference to the string instead of copying it
  std::map<std::pair<sourcemeta::jsontoolkit::JSON::String, Type>,
           std::uint64_t>
      strings;
  // A mirror of the above map to be able to sort by offset.
  // While this means we need 2x the amount of memory to keep track
  // of strings, it allows us to efficiently put an upper bound
  // on the amount of memory being consumed by this class.
  std::map<std::uint64_t,
           std::pair<sourcemeta::jsontoolkit::JSON::String, Type>>
      offsets;
  std::uint64_t byte_size = 0;
#if defined(_MSC_VER)
#pragma warning(default : 4251 4275)
#endif
};

} // namespace sourcemeta::jsonbinpack

#endif
#endif
