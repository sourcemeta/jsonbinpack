#include <sourcemeta/jsonbinpack/runtime_encoder.h>

#include <cassert> // assert
#include <cstdlib> // std::abort
#include <variant> // std::get

namespace sourcemeta::jsonbinpack {

Encoder::Encoder(Stream &output) : OutputStream{output} {}

auto Encoder::write(const sourcemeta::jsontoolkit::JSON &document,
                    const Plan &encoding) -> void {
  switch (encoding.index()) {
#define HANDLE_ENCODING(index, name)                                           \
  case (index):                                                                \
    return this->name(document,                                                \
                      std::get<sourcemeta::jsonbinpack::name>(encoding));
    HANDLE_ENCODING(0, BOUNDED_MULTIPLE_8BITS_ENUM_FIXED)
    HANDLE_ENCODING(1, FLOOR_MULTIPLE_ENUM_VARINT)
    HANDLE_ENCODING(2, ROOF_MULTIPLE_MIRROR_ENUM_VARINT)
    HANDLE_ENCODING(3, ARBITRARY_MULTIPLE_ZIGZAG_VARINT)
    HANDLE_ENCODING(4, DOUBLE_VARINT_TUPLE)
    HANDLE_ENCODING(5, BYTE_CHOICE_INDEX)
    HANDLE_ENCODING(6, LARGE_CHOICE_INDEX)
    HANDLE_ENCODING(7, TOP_LEVEL_BYTE_CHOICE_INDEX)
    HANDLE_ENCODING(8, CONST_NONE)
    HANDLE_ENCODING(9, UTF8_STRING_NO_LENGTH)
    HANDLE_ENCODING(10, FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED)
    HANDLE_ENCODING(11, ROOF_VARINT_PREFIX_UTF8_STRING_SHARED)
    HANDLE_ENCODING(12, BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED)
    HANDLE_ENCODING(13, RFC3339_DATE_INTEGER_TRIPLET)
    HANDLE_ENCODING(14, PREFIX_VARINT_LENGTH_STRING_SHARED)
    HANDLE_ENCODING(15, FIXED_TYPED_ARRAY)
    HANDLE_ENCODING(16, BOUNDED_8BITS_TYPED_ARRAY)
    HANDLE_ENCODING(17, FLOOR_TYPED_ARRAY)
    HANDLE_ENCODING(18, ROOF_TYPED_ARRAY)
    HANDLE_ENCODING(19, FIXED_TYPED_ARBITRARY_OBJECT)
    HANDLE_ENCODING(20, VARINT_TYPED_ARBITRARY_OBJECT)
    HANDLE_ENCODING(21, ANY_PACKED_TYPE_TAG_BYTE_PREFIX)
#undef HANDLE_ENCODING
  }

  // We should never get here. If so, it is definitely a bug
  assert(false);
  std::abort();
}

} // namespace sourcemeta::jsonbinpack
