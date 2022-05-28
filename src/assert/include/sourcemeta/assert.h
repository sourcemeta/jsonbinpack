#ifndef SOURCEMETA_ASSERT_ASSERT_H_
#define SOURCEMETA_ASSERT_ASSERT_H_

#include <stdexcept> // std::runtime_error
#include <string>    // std::string

namespace sourcemeta::assert {
inline auto CHECK(bool condition, const std::string &message) -> void {
  if (!condition) {
    throw std::runtime_error(message);
  }
}
} // namespace sourcemeta::assert

#endif
