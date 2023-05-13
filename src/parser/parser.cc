#include <jsonbinpack/parser/parser.h>

#include <sstream>   // std::ostringstream
#include <stdexcept> // std::runtime_error
#include <string>    // std::string

namespace sourcemeta::jsonbinpack {

auto parse(const sourcemeta::jsontoolkit::Value &input) -> Encoding {
  const auto encoding{sourcemeta::jsontoolkit::to_string(
      sourcemeta::jsontoolkit::at(input, "name"))};
  const auto &options{sourcemeta::jsontoolkit::at(input, "options")};
  if (encoding == "CONST_NONE") {
    assert(sourcemeta::jsontoolkit::defines(options, "value"));
    return CONST_NONE(sourcemeta::jsontoolkit::at(options, "value"));
  } else {
    std::ostringstream error;
    error << "Unrecognized encoding: " << encoding;
    throw std::runtime_error(error.str());
  }
}

} // namespace sourcemeta::jsonbinpack
