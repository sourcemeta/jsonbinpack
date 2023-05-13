#ifndef SOURCEMETA_JSONBINPACK_ENCODING_ENCODING_H_
#define SOURCEMETA_JSONBINPACK_ENCODING_ENCODING_H_

/// @defgroup encoding Encodings

#include <jsontoolkit/json.h>

#include <cstdint> // std::int64_t, std::uint64_t
#include <memory>  // std::shared_ptr
#include <variant> // std::variant
#include <vector>  // std::vector

namespace sourcemeta::jsonbinpack {

// We cannot directly create an Encoding variant type whose values potentially
// include other Encoding instances.  As a workaround, we have a helper
// encoding wrapper that we can use as an incomplete type
struct __internal_encoding_wrapper;
// Use these alias types. Never use the internal wrapper type directly
using SingleEncoding = std::shared_ptr<__internal_encoding_wrapper>;
using MultipleEncodings = std::vector<__internal_encoding_wrapper>;

/// @ingroup encoding
/// @defgroup encoding_integer Integer
/// @{

/// @brief The encoding consists of the integer value divided by the
/// `multiplier`, minus the ceil of `minimum` divided by the `multiplier`,
/// encoded as an 8-bit fixed-length unsigned integer.
struct BOUNDED_MULTIPLE_8BITS_ENUM_FIXED {
  /// The inclusive minimum value
  const std::int64_t minimum;
  /// The inclusive maximum value
  const std::int64_t maximum;
  /// The multiplier value
  const std::uint64_t multiplier;
};

/// @brief The encoding consists of the integer value divided by the
/// `multiplier`, minus the ceil of `minimum` divided by the `multiplier`,
/// encoded as a Base-128 64-bit Little Endian variable-length unsigned
/// integer.
struct FLOOR_MULTIPLE_ENUM_VARINT {
  /// The inclusive minimum value
  const std::int64_t minimum;
  /// The multiplier value
  const std::uint64_t multiplier;
};

/// @brief The encoding consists of the floor of `maximum` divided by the
/// `multiplier`, minus the integer value divided by the `multiplier`, encoded
/// as a Base-128 64-bit Little Endian variable-length unsigned integer.
struct ROOF_MULTIPLE_MIRROR_ENUM_VARINT {
  /// The inclusive maximum value
  const std::int64_t maximum;
  /// The multiplier value
  const std::uint64_t multiplier;
};

/// @brief The encoding consists of the the integer value divided by the
/// `multiplier` encoded as a ZigZag-encoded Base-128 64-bit Little Endian
/// variable-length unsigned integer.
struct ARBITRARY_MULTIPLE_ZIGZAG_VARINT {
  /// The multiplier value
  const std::uint64_t multiplier;
};

/// @}

/// @ingroup encoding
/// @defgroup encoding_number Number
/// @{

/// @brief The encoding consists of a sequence of two integers: The signed
/// integer that results from concatenating the integral part and the decimal
/// part of the number, if any, as a ZigZag-encoded Base-128 64-bit Little
/// Endian variable-length unsigned integer; and the position of the decimal
/// mark from the last digit of the number encoded as a Base-128 64-bit Little
/// Endian variable-length unsigned integer.
struct DOUBLE_VARINT_TUPLE {};

/// @}

/// @ingroup encoding
/// @defgroup encoding_enum Enumeration
/// @{

/// @brief The encoding consists of an index to the enumeration choices encoded
/// as an 8-bit fixed-length unsigned integer.
struct BYTE_CHOICE_INDEX {
#ifndef DOXYGEN
  // Because JSON documents are not easily copyable
  BYTE_CHOICE_INDEX(const BYTE_CHOICE_INDEX &);
  BYTE_CHOICE_INDEX(std::vector<sourcemeta::jsontoolkit::JSON> &&);
#endif
  /// The set of choice values
  const std::vector<sourcemeta::jsontoolkit::JSON> choices;
};

/// @brief The encoding consists of an index to the enumeration choices encoded
/// as a Base-128 64-bit Little Endian variable-length unsigned integer.
struct LARGE_CHOICE_INDEX {
#ifndef DOXYGEN
  // Because JSON documents are not easily copyable
  LARGE_CHOICE_INDEX(const LARGE_CHOICE_INDEX &);
  LARGE_CHOICE_INDEX(std::vector<sourcemeta::jsontoolkit::JSON> &&);
#endif
  /// The set of choice values
  const std::vector<sourcemeta::jsontoolkit::JSON> choices;
};

/// @brief If the input value corresponds to the index 0 to the enumeration
/// choices, the encoding stores no data. Otherwise, the encoding consists of
/// an index to the enumeration choices minus 1 encoded as an 8-bit
/// fixed-length unsigned integer.
struct TOP_LEVEL_BYTE_CHOICE_INDEX {
#ifndef DOXYGEN
  // Because JSON documents are not easily copyable
  TOP_LEVEL_BYTE_CHOICE_INDEX(const TOP_LEVEL_BYTE_CHOICE_INDEX &);
  TOP_LEVEL_BYTE_CHOICE_INDEX(std::vector<sourcemeta::jsontoolkit::JSON> &&);
#endif
  /// The set of choice values
  const std::vector<sourcemeta::jsontoolkit::JSON> choices;
};

/// @brief The constant input value is not encoded.
struct CONST_NONE {
#ifndef DOXYGEN
  // These constructors allow this encoding to be movable
  CONST_NONE(const sourcemeta::jsontoolkit::JSON &);
  CONST_NONE(const sourcemeta::jsontoolkit::Value &);
  CONST_NONE(const CONST_NONE &);
#endif
  /// The constant value
  const sourcemeta::jsontoolkit::JSON value;
};

/// @}

/// @ingroup encoding
/// @defgroup encoding_string String
/// @{

/// @brief The encoding consist in the UTF-8 encoding of the input string.
struct UTF8_STRING_NO_LENGTH {
  /// The string UTF-8 byte-length
  const std::uint64_t size;
};

/// @brief The encoding consists of the byte-length of the string minus
/// `minimum` plus 1 as a Base-128 64-bit Little Endian variable-length
/// unsigned integer followed by the UTF-8 encoding of the input value.
///
/// Optionally, if the input string has already been encoded to the buffer
/// using UTF-8, the encoding may consist of the byte constant `0x00` followed
/// by the byte-length of the string minus `minimum` plus 1 as a Base-128
/// 64-bit Little Endian variable-length unsigned integer, followed by the
/// current offset minus the offset to the start of the UTF-8 string value in
/// the buffer encoded as a Base-128 64-bit Little Endian variable-length
/// unsigned integer.
struct FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED {
  /// The inclusive minimum string UTF-8 byte-length
  const std::uint64_t minimum;
};

/// @brief The encoding consists of `maximum` minus the byte-length of the
/// string plus 1 as a Base-128 64-bit Little Endian variable-length unsigned
/// integer followed by the UTF-8 encoding of the input value.
///
/// Optionally, if the input string has already been encoded to the buffer
/// using UTF-8, the encoding may consist of the byte constant `0x00` followed
/// by `maximum` minus the byte-length of the string plus 1 as a Base-128
/// 64-bit Little Endian variable-length unsigned integer, followed by the
/// current offset minus the offset to the start of the UTF-8 string value in
/// the buffer encoded as a Base-128 64-bit Little Endian variable-length
/// unsigned integer.
struct ROOF_VARINT_PREFIX_UTF8_STRING_SHARED {
  /// The inclusive maximum string UTF-8 byte-length
  const std::uint64_t maximum;
};

/// @brief The encoding consists of the byte-length of the string minus
/// `minimum` plus 1 as an 8-bit fixed-length unsigned integer followed by the
/// UTF-8 encoding of the input value.
///
/// Optionally, if the input string has already been encoded to the buffer
/// using UTF-8, the encoding may consist of the byte constant `0x00` followed
/// by the byte-length of the string minus `minimum` plus 1 as an 8-bit
/// fixed-length unsigned integer, followed by the current offset minus the
/// offset to the start of the UTF-8 string value in the buffer encoded as a
/// Base-128 64-bit Little Endian variable-length unsigned integer.
///
/// The byte-length of the string is encoded even if `maximum` equals `minimum`
/// in order to disambiguate between shared and non-shared fixed strings.
struct BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED {
  /// The inclusive minimum string UTF-8 byte-length
  const std::uint64_t minimum;
  /// The inclusive maximum string UTF-8 byte-length
  const std::uint64_t maximum;
};

/// @brief The encoding consists of an implementation of
/// [RFC3339](https://datatracker.ietf.org/doc/html/rfc3339) date expressions
/// as the sequence of 3 integers: the year as a 16-bit fixed-length Little
/// Endian unsigned integer, the month as an 8-bit fixed-length unsigned
/// integer, and the day as an 8-bit fixed-length unsigned integer.
struct RFC3339_DATE_INTEGER_TRIPLET {};

/// @}

/// @ingroup encoding
/// @defgroup encoding_array Array
/// @{

/// @brief The encoding consists of the elements of the fixed array encoded in
/// order. The encoding of the element at index `i` is either
/// `prefix_encodings[i]` if set, or `encoding`.
struct FIXED_TYPED_ARRAY {
  /// The array length
  const std::uint64_t size;
  /// Element encoding
  const SingleEncoding encoding;
  /// Positional encodings
  const MultipleEncodings prefix_encodings;
};

/// @brief The encoding consists of the length of the array minus `minimum`
/// encoded as an 8-bit fixed-length unsigned integer followed by the elements
/// of the array encoded in order. The encoding of the element at index `i` is
/// either `prefix_encodings[i]` if set, or `encoding`.
struct BOUNDED_8BITS_TYPED_ARRAY {
  /// The minimum length of the array
  const std::uint64_t minimum;
  /// The maximum length of the array
  const std::uint64_t maximum;
  /// Element encoding
  const SingleEncoding encoding;
  /// Positional encodings
  const MultipleEncodings prefix_encodings;
};

/// @brief The encoding consists of the length of the array minus `minimum`
/// encoded as a Base-128 64-bit Little Endian variable-length unsigned integer
/// followed by the elements of the array encoded in order. The encoding of the
/// element at index `i` is either `prefix_encodings[i]` if set, or `encoding`.
struct FLOOR_TYPED_ARRAY {
  /// The minimum length of the array
  const std::uint64_t minimum;
  /// Element encoding
  const SingleEncoding encoding;
  /// Positional encodings
  const MultipleEncodings prefix_encodings;
};

/// @brief The encoding consists of `maximum` minus the length of the array
/// encoded as a Base-128 64-bit Little Endian variable-length unsigned integer
/// followed by the elements of the array encoded in order. The encoding of the
/// element at index `i` is either `prefix_encodings[i]` if set, or `encoding`.
struct ROOF_TYPED_ARRAY {
  /// The maximum length of the array
  const std::uint64_t maximum;
  /// Element encoding
  const SingleEncoding encoding;
  /// Positional encodings
  const MultipleEncodings prefix_encodings;
};

/// @}

// Encoding type

using Encoding = std::variant<
    BOUNDED_MULTIPLE_8BITS_ENUM_FIXED, FLOOR_MULTIPLE_ENUM_VARINT,
    ROOF_MULTIPLE_MIRROR_ENUM_VARINT, ARBITRARY_MULTIPLE_ZIGZAG_VARINT,
    DOUBLE_VARINT_TUPLE, BYTE_CHOICE_INDEX, LARGE_CHOICE_INDEX,
    TOP_LEVEL_BYTE_CHOICE_INDEX, CONST_NONE, UTF8_STRING_NO_LENGTH,
    FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED,
    ROOF_VARINT_PREFIX_UTF8_STRING_SHARED,
    BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED, RFC3339_DATE_INTEGER_TRIPLET,
    FIXED_TYPED_ARRAY, BOUNDED_8BITS_TYPED_ARRAY, FLOOR_TYPED_ARRAY,
    ROOF_TYPED_ARRAY>;

// Helper definitions that rely on the Encoding data type
#ifndef DOXYGEN
// Ignore this definition on the documentation
struct __internal_encoding_wrapper {
  const Encoding value;
};
#endif

} // namespace sourcemeta::jsonbinpack

#endif
