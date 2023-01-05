#include <jsonbinpack/encoder/context.h>

#include <cassert>   // assert
#include <iterator>  // std::cbegin, std::cend
#include <stdexcept> // std::logic_error

// Encoding a shared string has some overhead, such as the
// shared string marker + the offset, so its not worth
// doing for strings that are too small.
static constexpr auto MINIMUM_STRING_LENGTH{3};

// We don't want to allow the context to grow
// forever, otherwise an attacker could force the
// program to exhaust memory given an input
// document that contains a high number of large strings.
static constexpr auto MAXIMUM_BYTE_SIZE{20971520};

auto sourcemeta::jsonbinpack::encoder::Context::record(
    const std::string &value, const std::uint64_t offset) -> void {
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

auto sourcemeta::jsonbinpack::encoder::Context::remove_oldest() -> void {
  assert(!this->strings.empty());
  // std::map are by definition ordered by key,
  // so the begin iterator points to the entry
  // with the lowest offset, a.k.a. the oldest.
  const auto iterator{std::cbegin(this->offsets)};
  this->strings.erase(iterator->second);
  this->byte_size -= iterator->second.size();
  this->offsets.erase(iterator);
}

auto sourcemeta::jsonbinpack::encoder::Context::has(
    const std::string &value) const -> bool {
  return this->strings.contains(value);
}

auto sourcemeta::jsonbinpack::encoder::Context::offset(
    const std::string &value) const -> std::uint64_t {
  // This method assumes the value indeed exists for performance reasons
  assert(this->has(value));
  return this->strings.at(value);
}
