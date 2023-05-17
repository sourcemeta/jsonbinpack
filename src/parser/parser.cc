#include <jsonbinpack/encoding/wrap.h>
#include <jsonbinpack/parser/parser.h>

#include "v1_enum.h"
#include "v1_integer.h"
#include "v1_number.h"
#include "v1_string.h"

#include <algorithm> // std::transform
#include <cstdint>   // std::uint64_t
#include <iterator>  // std::back_inserter
#include <sstream>   // std::ostringstream
#include <stdexcept> // std::runtime_error
#include <string>    // std::string
#include <vector>    // std::vector

namespace sourcemeta::jsonbinpack {

// TODO: Reduce the size of this function, by creating a parse function
// for each encoding (taken its options as arguments)
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
    assert(sourcemeta::jsontoolkit::defines(options, "size"));
    assert(sourcemeta::jsontoolkit::defines(options, "encoding"));
    assert(sourcemeta::jsontoolkit::defines(options, "prefixEncodings"));
    const auto &size{sourcemeta::jsontoolkit::at(options, "size")};
    const auto &array_encoding{
        sourcemeta::jsontoolkit::at(options, "encoding")};
    const auto &prefix_encodings{
        sourcemeta::jsontoolkit::at(options, "prefixEncodings")};
    assert(sourcemeta::jsontoolkit::is_integer(size));
    assert(sourcemeta::jsontoolkit::is_positive(size));
    assert(sourcemeta::jsontoolkit::is_object(array_encoding));
    assert(sourcemeta::jsontoolkit::is_array(prefix_encodings));
    std::vector<Encoding> encodings;
    std::transform(sourcemeta::jsontoolkit::cbegin_array(prefix_encodings),
                   sourcemeta::jsontoolkit::cend_array(prefix_encodings),
                   std::back_inserter(encodings),
                   [](const auto &element) { return parse(element); });
    assert(encodings.size() == sourcemeta::jsontoolkit::size(prefix_encodings));
    return FIXED_TYPED_ARRAY{
        static_cast<std::uint64_t>(sourcemeta::jsontoolkit::to_integer(size)),
        wrap(parse(array_encoding)), wrap(encodings.begin(), encodings.end())};
  }

  std::ostringstream error;
  error << "Unrecognized encoding: " << encoding;
  throw std::runtime_error(error.str());
}

} // namespace sourcemeta::jsonbinpack
