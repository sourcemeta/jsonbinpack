#ifndef SOURCEMETA_JSONBINPACK_OPTIONS_OPTIONS_H_
#define SOURCEMETA_JSONBINPACK_OPTIONS_OPTIONS_H_

#include <jsontoolkit/json.h>

#include <cstdint> // std::int64_t, std::uint64_t
#include <memory>  // std::shared_ptr
#include <variant> // std::variant
#include <vector>  // std::vector

namespace sourcemeta::jsonbinpack::options {

// We cannot directly create an Encoding variant type whose values potentially
// include other Encoding instances.  As a workaround, we have a helper
// encoding wrapper that we can use as an incomplete type
struct __internal_encoding_wrapper;
// Use these alias types. Never use the internal wrapper type directly
using SingleEncoding = std::shared_ptr<__internal_encoding_wrapper>;
using MultipleEncodings = std::vector<__internal_encoding_wrapper>;

// Integers

struct BOUNDED_MULTIPLE_8BITS_ENUM_FIXED {
  const std::int64_t minimum;
  const std::int64_t maximum;
  const std::uint64_t multiplier;
};

struct FLOOR_MULTIPLE_ENUM_VARINT {
  const std::int64_t minimum;
  const std::uint64_t multiplier;
};

struct ROOF_MULTIPLE_MIRROR_ENUM_VARINT {
  const std::int64_t maximum;
  const std::uint64_t multiplier;
};

struct ARBITRARY_MULTIPLE_ZIGZAG_VARINT {
  const std::uint64_t multiplier;
};

// Number

struct DOUBLE_VARINT_TUPLE {};

// Enumerations

struct BYTE_CHOICE_INDEX {
  // Because JSON documents are not easily copyable
  BYTE_CHOICE_INDEX(const BYTE_CHOICE_INDEX &);
  BYTE_CHOICE_INDEX(std::vector<sourcemeta::jsontoolkit::JSON> &&);
  const std::vector<sourcemeta::jsontoolkit::JSON> choices;
};

struct LARGE_CHOICE_INDEX {
  // Because JSON documents are not easily copyable
  LARGE_CHOICE_INDEX(const LARGE_CHOICE_INDEX &);
  LARGE_CHOICE_INDEX(std::vector<sourcemeta::jsontoolkit::JSON> &&);
  const std::vector<sourcemeta::jsontoolkit::JSON> choices;
};

struct TOP_LEVEL_BYTE_CHOICE_INDEX {
  // Because JSON documents are not easily copyable
  TOP_LEVEL_BYTE_CHOICE_INDEX(const TOP_LEVEL_BYTE_CHOICE_INDEX &);
  TOP_LEVEL_BYTE_CHOICE_INDEX(std::vector<sourcemeta::jsontoolkit::JSON> &&);
  const std::vector<sourcemeta::jsontoolkit::JSON> choices;
};

struct CONST_NONE {
  // These constructors allow this encoding to be movable
  CONST_NONE(const sourcemeta::jsontoolkit::JSON &);
  CONST_NONE(const CONST_NONE &);
  const sourcemeta::jsontoolkit::JSON value;
};

// Strings

struct UTF8_STRING_NO_LENGTH {
  const std::uint64_t size;
};

struct FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED {
  const std::uint64_t minimum;
};

struct ROOF_VARINT_PREFIX_UTF8_STRING_SHARED {
  const std::uint64_t maximum;
};

struct BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED {
  const std::uint64_t minimum;
  const std::uint64_t maximum;
};

struct RFC3339_DATE_INTEGER_TRIPLET {};

// Encoding type

using Encoding = std::variant<
    BOUNDED_MULTIPLE_8BITS_ENUM_FIXED, FLOOR_MULTIPLE_ENUM_VARINT,
    ROOF_MULTIPLE_MIRROR_ENUM_VARINT, ARBITRARY_MULTIPLE_ZIGZAG_VARINT,
    DOUBLE_VARINT_TUPLE, BYTE_CHOICE_INDEX, LARGE_CHOICE_INDEX,
    TOP_LEVEL_BYTE_CHOICE_INDEX, CONST_NONE, UTF8_STRING_NO_LENGTH,
    FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED,
    ROOF_VARINT_PREFIX_UTF8_STRING_SHARED,
    BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED, RFC3339_DATE_INTEGER_TRIPLET>;

// Helper definitions that rely on the Encoding data type
struct __internal_encoding_wrapper {
  const Encoding value;
};

} // namespace sourcemeta::jsonbinpack::options

#endif
