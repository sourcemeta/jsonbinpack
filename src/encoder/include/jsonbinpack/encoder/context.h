#ifndef SOURCEMETA_JSONBINPACK_ENCODER_CONTEXT_H_
#define SOURCEMETA_JSONBINPACK_ENCODER_CONTEXT_H_

#include <cassert>   // assert
#include <iterator>  // std::cbegin, std::cend
#include <map>       // std::map
#include <stdexcept> // std::logic_error

// Encoding a shared string has some overhead, such as the
// shared string marker + the offset, so its not worth
// doing for strings that are too small.
constexpr auto MINIMUM_STRING_LENGTH{3};

// We don't want to allow the context to grow
// forever, otherwise an attacker could force the
// program to exhaust memory given an input
// document that contains a high number of large strings.
constexpr auto MAXIMUM_BYTE_SIZE{20971520};

namespace sourcemeta::jsonbinpack::encoder {

template <typename Source, typename Offset> class Context {
public:
  auto record(const Source &value, const Offset offset) -> void {
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
    if (this->has(value)) {
      const auto previous_offset{this->strings[value]};
      if (offset > previous_offset) {
        this->strings[value] = offset;
        this->offsets.erase(previous_offset);
        this->offsets.insert({offset, value});
      }
    } else {
      const auto result{this->offsets.insert({offset, value})};
      // Prevent recording two strings to the same offset
      assert(result.second);
      if (result.second) {
        this->strings.insert({value, offset});
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
    this->strings.erase(iterator->second);
    this->byte_size -= iterator->second.size();
    this->offsets.erase(iterator);
  }

  auto has(const Source &value) const -> bool {
    // TODO: Use .contains() in C++20
    // See https://en.cppreference.com/w/cpp/container/map/contains
    return this->strings.find(value) != std::cend(this->strings);
  }

  auto offset(const Source &value) const -> Offset {
    // This method assumes the value indeed exists for performance reasons
    assert(this->has(value));
    return this->strings.at(value);
  }

private:
  std::map<Source, Offset> strings;
  // A mirror of the above map to be able to sort by offset.
  // While this means we need 2x the amount of memory to keep track
  // of strings, it allows us to efficiently put an upper bound
  // on the amount of memory being consumed by this class.
  std::map<Offset, Source> offsets;
  std::uint64_t byte_size = 0;
};

} // namespace sourcemeta::jsonbinpack::encoder

#endif
