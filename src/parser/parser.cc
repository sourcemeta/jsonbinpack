#include <jsonbinpack/parser/parser.h>

#include "v1_array.h"
#include "v1_enum.h"
#include "v1_integer.h"
#include "v1_number.h"
#include "v1_string.h"

#include <cassert>   // assert
#include <sstream>   // std::ostringstream
#include <stdexcept> // std::runtime_error

namespace sourcemeta::jsonbinpack {

auto parse(const sourcemeta::jsontoolkit::Value &input) -> Encoding {
  assert(sourcemeta::jsontoolkit::defines(input, "name"));
  assert(sourcemeta::jsontoolkit::defines(input, "options"));
  const auto encoding{sourcemeta::jsontoolkit::to_string(
      sourcemeta::jsontoolkit::at(input, "name"))};
  const auto &options{sourcemeta::jsontoolkit::at(input, "options")};

  // Integers
  if (encoding == "BOUNDED_MULTIPLE_8BITS_ENUM_FIXED") {
    return parser::v1::BOUNDED_MULTIPLE_8BITS_ENUM_FIXED(options);
  } else if (encoding == "FLOOR_MULTIPLE_ENUM_VARINT") {
    return parser::v1::FLOOR_MULTIPLE_ENUM_VARINT(options);
  } else if (encoding == "ROOF_MULTIPLE_MIRROR_ENUM_VARINT") {
    return parser::v1::ROOF_MULTIPLE_MIRROR_ENUM_VARINT(options);
  } else if (encoding == "ARBITRARY_MULTIPLE_ZIGZAG_VARINT") {
    return parser::v1::ARBITRARY_MULTIPLE_ZIGZAG_VARINT(options);

    // Numbers
  } else if (encoding == "DOUBLE_VARINT_TUPLE") {
    return parser::v1::DOUBLE_VARINT_TUPLE(options);

    // Enumerations
  } else if (encoding == "BYTE_CHOICE_INDEX") {
    return parser::v1::BYTE_CHOICE_INDEX(options);
  } else if (encoding == "LARGE_CHOICE_INDEX") {
    return parser::v1::LARGE_CHOICE_INDEX(options);
  } else if (encoding == "TOP_LEVEL_BYTE_CHOICE_INDEX") {
    return parser::v1::TOP_LEVEL_BYTE_CHOICE_INDEX(options);
  } else if (encoding == "CONST_NONE") {
    return parser::v1::CONST_NONE(options);

    // Strings
  } else if (encoding == "UTF8_STRING_NO_LENGTH") {
    return parser::v1::UTF8_STRING_NO_LENGTH(options);
  } else if (encoding == "FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED") {
    return parser::v1::FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED(options);
  } else if (encoding == "ROOF_VARINT_PREFIX_UTF8_STRING_SHARED") {
    return parser::v1::ROOF_VARINT_PREFIX_UTF8_STRING_SHARED(options);
  } else if (encoding == "BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED") {
    return parser::v1::BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED(options);
  } else if (encoding == "RFC3339_DATE_INTEGER_TRIPLET") {
    return parser::v1::RFC3339_DATE_INTEGER_TRIPLET(options);

    // Arrays
  } else if (encoding == "FIXED_TYPED_ARRAY") {
    return parser::v1::FIXED_TYPED_ARRAY(options);
  }

  std::ostringstream error;
  error << "Unrecognized encoding: " << encoding;
  throw std::runtime_error(error.str());
}

} // namespace sourcemeta::jsonbinpack
