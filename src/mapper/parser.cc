#include <jsonbinpack/encoding/encoding.h>
#include <jsonbinpack/mapper/encoding.h>
#include <jsonbinpack/mapper/parser.h>

#include <cassert>   // assert
#include <sstream>   // std::ostringstream
#include <stdexcept> // std::runtime_error
#include <string>    // std::string

namespace sourcemeta::jsonbinpack::mapper {

auto parse(const sourcemeta::jsontoolkit::Value &input) -> Encoding {
  assert(is_encoding(input));
  const auto encoding{sourcemeta::jsontoolkit::to_string(
      sourcemeta::jsontoolkit::at(input, keywords::name))};
  const auto &options{sourcemeta::jsontoolkit::at(input, keywords::options)};
  if (encoding == "CONST_NONE") {
    assert(sourcemeta::jsontoolkit::defines(options, "value"));
    return CONST_NONE(sourcemeta::jsontoolkit::at(options, "value"));
  } else {
    std::ostringstream error;
    error << "Unrecognized encoding: " << encoding;
    throw std::runtime_error(error.str());
  }
}

} // namespace sourcemeta::jsonbinpack::mapper
