#ifndef SOURCEMETA_JSONBINPACK_RUNTIME_ENCODER_H_
#define SOURCEMETA_JSONBINPACK_RUNTIME_ENCODER_H_

#include "runtime_export.h"

#include <sourcemeta/jsonbinpack/runtime_encoder_cache.h>
#include <sourcemeta/jsonbinpack/runtime_encoding.h>
#include <sourcemeta/jsonbinpack/runtime_output_stream.h>

#include <sourcemeta/jsontoolkit/json.h>

namespace sourcemeta::jsonbinpack {

/// @ingroup runtime
class SOURCEMETA_JSONBINPACK_RUNTIME_EXPORT Encoder : private OutputStream {
public:
  Encoder(Stream &output);
  auto write(const sourcemeta::jsontoolkit::JSON &document,
             const Encoding &encoding) -> void;

// The methods that implement individual encodings as considered private
#ifndef DOXYGEN
#define DECLARE_ENCODING(name)                                                 \
  auto name(const sourcemeta::jsontoolkit::JSON &document, const name &)       \
      -> void;

  // Integer
  DECLARE_ENCODING(BOUNDED_MULTIPLE_8BITS_ENUM_FIXED)
  DECLARE_ENCODING(FLOOR_MULTIPLE_ENUM_VARINT)
  DECLARE_ENCODING(ROOF_MULTIPLE_MIRROR_ENUM_VARINT)
  DECLARE_ENCODING(ARBITRARY_MULTIPLE_ZIGZAG_VARINT)

  // Number
  DECLARE_ENCODING(DOUBLE_VARINT_TUPLE)

  // Any
  DECLARE_ENCODING(BYTE_CHOICE_INDEX)
  DECLARE_ENCODING(LARGE_CHOICE_INDEX)
  DECLARE_ENCODING(TOP_LEVEL_BYTE_CHOICE_INDEX)
  DECLARE_ENCODING(CONST_NONE)
  DECLARE_ENCODING(ANY_PACKED_TYPE_TAG_BYTE_PREFIX)

  // String
  DECLARE_ENCODING(UTF8_STRING_NO_LENGTH)
  DECLARE_ENCODING(FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED)
  DECLARE_ENCODING(ROOF_VARINT_PREFIX_UTF8_STRING_SHARED)
  DECLARE_ENCODING(BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED)
  DECLARE_ENCODING(RFC3339_DATE_INTEGER_TRIPLET)
  DECLARE_ENCODING(PREFIX_VARINT_LENGTH_STRING_SHARED)
  // TODO: Implement STRING_BROTLI encoding
  // TODO: Implement STRING_DICTIONARY_COMPRESSOR encoding
  // TODO: Implement STRING_UNBOUNDED_SCOPED_PREFIX_LENGTH encoding
  // TODO: Implement URL_PROTOCOL_HOST_REST encoding

  // Array
  DECLARE_ENCODING(FIXED_TYPED_ARRAY)
  DECLARE_ENCODING(BOUNDED_8BITS_TYPED_ARRAY)
  DECLARE_ENCODING(FLOOR_TYPED_ARRAY)
  DECLARE_ENCODING(ROOF_TYPED_ARRAY)

  // Object
  DECLARE_ENCODING(FIXED_TYPED_ARBITRARY_OBJECT)
  DECLARE_ENCODING(VARINT_TYPED_ARBITRARY_OBJECT)

#undef DECLARE_ENCODING
#endif

private:
  Cache cache_;
};

} // namespace sourcemeta::jsonbinpack

#endif
