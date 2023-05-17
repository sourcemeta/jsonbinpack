#include <jsonbinpack/encoding/wrap.h>
#include <jsonbinpack/parser/parser.h>

#include "v1_integer.h"

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
    return DOUBLE_VARINT_TUPLE{};

    // Enumerations
  } else if (encoding == "BYTE_CHOICE_INDEX") {
    assert(sourcemeta::jsontoolkit::defines(options, "choices"));
    const auto &choices{sourcemeta::jsontoolkit::at(options, "choices")};
    assert(sourcemeta::jsontoolkit::is_array(choices));
    return BYTE_CHOICE_INDEX(sourcemeta::jsontoolkit::to_vector(choices));
  } else if (encoding == "LARGE_CHOICE_INDEX") {
    assert(sourcemeta::jsontoolkit::defines(options, "choices"));
    const auto &choices{sourcemeta::jsontoolkit::at(options, "choices")};
    assert(sourcemeta::jsontoolkit::is_array(choices));
    return LARGE_CHOICE_INDEX(sourcemeta::jsontoolkit::to_vector(choices));
  } else if (encoding == "TOP_LEVEL_BYTE_CHOICE_INDEX") {
    assert(sourcemeta::jsontoolkit::defines(options, "choices"));
    const auto &choices{sourcemeta::jsontoolkit::at(options, "choices")};
    assert(sourcemeta::jsontoolkit::is_array(choices));
    return TOP_LEVEL_BYTE_CHOICE_INDEX(
        sourcemeta::jsontoolkit::to_vector(choices));
  } else if (encoding == "CONST_NONE") {
    assert(sourcemeta::jsontoolkit::defines(options, "value"));
    return CONST_NONE(sourcemeta::jsontoolkit::at(options, "value"));

    // Strings
  } else if (encoding == "UTF8_STRING_NO_LENGTH") {
    assert(sourcemeta::jsontoolkit::defines(options, "size"));
    const auto &size{sourcemeta::jsontoolkit::at(options, "size")};
    assert(sourcemeta::jsontoolkit::is_integer(size));
    assert(sourcemeta::jsontoolkit::is_positive(size));
    return UTF8_STRING_NO_LENGTH{
        static_cast<std::uint64_t>(sourcemeta::jsontoolkit::to_integer(size))};
  } else if (encoding == "FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED") {
    assert(sourcemeta::jsontoolkit::defines(options, "minimum"));
    const auto &minimum{sourcemeta::jsontoolkit::at(options, "minimum")};
    assert(sourcemeta::jsontoolkit::is_integer(minimum));
    assert(sourcemeta::jsontoolkit::is_positive(minimum));
    return FLOOR_VARINT_PREFIX_UTF8_STRING_SHARED{static_cast<std::uint64_t>(
        sourcemeta::jsontoolkit::to_integer(minimum))};
  } else if (encoding == "ROOF_VARINT_PREFIX_UTF8_STRING_SHARED") {
    assert(sourcemeta::jsontoolkit::defines(options, "maximum"));
    const auto &maximum{sourcemeta::jsontoolkit::at(options, "maximum")};
    assert(sourcemeta::jsontoolkit::is_integer(maximum));
    assert(sourcemeta::jsontoolkit::is_positive(maximum));
    return ROOF_VARINT_PREFIX_UTF8_STRING_SHARED{static_cast<std::uint64_t>(
        sourcemeta::jsontoolkit::to_integer(maximum))};
  } else if (encoding == "BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED") {
    assert(sourcemeta::jsontoolkit::defines(options, "minimum"));
    assert(sourcemeta::jsontoolkit::defines(options, "maximum"));
    const auto &minimum{sourcemeta::jsontoolkit::at(options, "minimum")};
    const auto &maximum{sourcemeta::jsontoolkit::at(options, "maximum")};
    assert(sourcemeta::jsontoolkit::is_integer(minimum));
    assert(sourcemeta::jsontoolkit::is_integer(maximum));
    assert(sourcemeta::jsontoolkit::is_positive(minimum));
    assert(sourcemeta::jsontoolkit::is_positive(maximum));
    return BOUNDED_8BIT_PREFIX_UTF8_STRING_SHARED{
        static_cast<std::uint64_t>(
            sourcemeta::jsontoolkit::to_integer(minimum)),
        static_cast<std::uint64_t>(
            sourcemeta::jsontoolkit::to_integer(maximum))};
  } else if (encoding == "RFC3339_DATE_INTEGER_TRIPLET") {
    return RFC3339_DATE_INTEGER_TRIPLET{};

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
