// Copyright (c) 2021 Juan Cruz Viotti. All rights reserved.

#include "jsonbinpack/utils/zigzag.h"

#include <cstdint>

// See Protocol Buffers' ZigZag encoding definition:
// https://developers.google.com/protocol-buffers/docs/encoding

std::uint64_t jsonbinpack::utils::ZigzagEncode(
    const std::int64_t value) noexcept {
  if (value >= 0) {
    return static_cast<std::uint64_t>(value * 2);
  }

  return static_cast<std::uint64_t>((value * -2) - 1);
}

std::int64_t jsonbinpack::utils::ZigzagDecode(
    const std::uint64_t value) noexcept {
  return static_cast<std::int64_t>(value);
}
