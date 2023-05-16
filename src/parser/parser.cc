#include <jsonbinpack/parser/parser.h>

#include <cstdint>   // std::uint64_t
#include <sstream>   // std::ostringstream
#include <stdexcept> // std::runtime_error
#include <string>    // std::string

namespace sourcemeta::jsonbinpack {

auto parse(const sourcemeta::jsontoolkit::Value &input) -> Encoding {
  assert(sourcemeta::jsontoolkit::defines(input, "name"));
  assert(sourcemeta::jsontoolkit::defines(input, "options"));
  const auto encoding{sourcemeta::jsontoolkit::to_string(
      sourcemeta::jsontoolkit::at(input, "name"))};
  const auto &options{sourcemeta::jsontoolkit::at(input, "options")};

  // Integers
  if (encoding == "BOUNDED_MULTIPLE_8BITS_ENUM_FIXED") {
    assert(sourcemeta::jsontoolkit::defines(options, "minimum"));
    assert(sourcemeta::jsontoolkit::defines(options, "maximum"));
    assert(sourcemeta::jsontoolkit::defines(options, "multiplier"));
    const auto &minimum{sourcemeta::jsontoolkit::at(options, "minimum")};
    const auto &maximum{sourcemeta::jsontoolkit::at(options, "maximum")};
    const auto &multiplier{sourcemeta::jsontoolkit::at(options, "multiplier")};
    return BOUNDED_MULTIPLE_8BITS_ENUM_FIXED{
        sourcemeta::jsontoolkit::to_integer(minimum),
        sourcemeta::jsontoolkit::to_integer(maximum),
        static_cast<std::uint64_t>(
            sourcemeta::jsontoolkit::to_integer(multiplier))};

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
  }

  std::ostringstream error;
  error << "Unrecognized encoding: " << encoding;
  throw std::runtime_error(error.str());
}

} // namespace sourcemeta::jsonbinpack