#ifndef SOURCEMETA_JSONBINPACK_ENCODING_TAG_H_
#define SOURCEMETA_JSONBINPACK_ENCODING_TAG_H_

#include <sourcemeta/jsonbinpack/numeric.h>

namespace sourcemeta::jsonbinpack::tag {

namespace ANY_PACKED_TYPE_TAG_BYTE_PREFIX {
constexpr auto type_size = 3;
constexpr std::uint8_t TYPE_SHARED_STRING = 0b00000000;
constexpr std::uint8_t TYPE_STRING = 0b00000001;
constexpr std::uint8_t TYPE_LONG_STRING = 0b00000010;
constexpr std::uint8_t TYPE_OBJECT = 0b00000011;
constexpr std::uint8_t TYPE_ARRAY = 0b00000100;
constexpr std::uint8_t TYPE_POSITIVE_INTEGER_BYTE = 0b00000101;
constexpr std::uint8_t TYPE_NEGATIVE_INTEGER_BYTE = 0b00000110;
constexpr std::uint8_t TYPE_OTHER = 0b00000111;
static_assert(TYPE_SHARED_STRING <= uint_max<type_size>);
static_assert(TYPE_STRING <= uint_max<type_size>);
static_assert(TYPE_LONG_STRING <= uint_max<type_size>);
static_assert(TYPE_OBJECT <= uint_max<type_size>);
static_assert(TYPE_ARRAY <= uint_max<type_size>);
static_assert(TYPE_POSITIVE_INTEGER_BYTE <= uint_max<type_size>);
static_assert(TYPE_NEGATIVE_INTEGER_BYTE <= uint_max<type_size>);
static_assert(TYPE_OTHER <= uint_max<type_size>);

constexpr auto subtype_size = 5;
constexpr std::uint8_t SUBTYPE_FALSE = 0b00000000;
constexpr std::uint8_t SUBTYPE_TRUE = 0b00000001;
constexpr std::uint8_t SUBTYPE_NULL = 0b00000010;
constexpr std::uint8_t SUBTYPE_POSITIVE_INTEGER = 0b00000011;
constexpr std::uint8_t SUBTYPE_NEGATIVE_INTEGER = 0b00000100;
constexpr std::uint8_t SUBTYPE_NUMBER = 0b00000101;
constexpr std::uint8_t SUBTYPE_LONG_STRING_BASE_EXPONENT_7 = 0b00000111;
constexpr std::uint8_t SUBTYPE_LONG_STRING_BASE_EXPONENT_8 = 0b00001000;
constexpr std::uint8_t SUBTYPE_LONG_STRING_BASE_EXPONENT_9 = 0b00001001;
constexpr std::uint8_t SUBTYPE_LONG_STRING_BASE_EXPONENT_10 = 0b00001010;

static_assert(SUBTYPE_FALSE <= uint_max<subtype_size>);
static_assert(SUBTYPE_TRUE <= uint_max<subtype_size>);
static_assert(SUBTYPE_NULL <= uint_max<subtype_size>);
static_assert(SUBTYPE_POSITIVE_INTEGER <= uint_max<subtype_size>);
static_assert(SUBTYPE_NEGATIVE_INTEGER <= uint_max<subtype_size>);
static_assert(SUBTYPE_NUMBER <= uint_max<subtype_size>);
static_assert(SUBTYPE_LONG_STRING_BASE_EXPONENT_7 <= uint_max<subtype_size>);
static_assert(SUBTYPE_LONG_STRING_BASE_EXPONENT_8 <= uint_max<subtype_size>);
static_assert(SUBTYPE_LONG_STRING_BASE_EXPONENT_9 <= uint_max<subtype_size>);
static_assert(SUBTYPE_LONG_STRING_BASE_EXPONENT_10 <= uint_max<subtype_size>);

// Note that the binary values actually match the declared exponents
static_assert(SUBTYPE_LONG_STRING_BASE_EXPONENT_7 == 7);
static_assert(SUBTYPE_LONG_STRING_BASE_EXPONENT_8 == 8);
static_assert(SUBTYPE_LONG_STRING_BASE_EXPONENT_9 == 9);
static_assert(SUBTYPE_LONG_STRING_BASE_EXPONENT_10 == 10);
} // namespace ANY_PACKED_TYPE_TAG_BYTE_PREFIX

} // namespace sourcemeta::jsonbinpack::tag

#endif
