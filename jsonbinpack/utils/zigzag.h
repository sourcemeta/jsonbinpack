// Copyright (c) 2021 Juan Cruz Viotti. All rights reserved.

#ifndef JSONBINPACK_UTILS_ZIGZAG_H_
#define JSONBINPACK_UTILS_ZIGZAG_H_

#include <cstdint>

namespace jsonbinpack {
namespace utils {

std::uint64_t ZigzagEncode(const std::int64_t) noexcept;
std::int64_t ZigzagDecode(const std::uint64_t) noexcept;

}  // namespace utils
}  // namespace jsonbinpack

#endif  // JSONBINPACK_UTILS_ZIGZAG_H_
