#ifndef SOURCEMETA_JSONBINPACK_MAPPER_UTILS_H_
#define SOURCEMETA_JSONBINPACK_MAPPER_UTILS_H_

#include <cassert> // assert
#include <jsonbinpack/mapper/format.h>
#include <jsontoolkit/json.h>
#include <map>    // std::map
#include <string> // std::string

namespace sourcemeta::jsonbinpack::mapper {

template <typename Source>
static auto make_encoding(
    sourcemeta::jsontoolkit::JSON<Source> &document, const std::string &type,
    const std::string encoding,
    const std::map<Source, sourcemeta::jsontoolkit::JSON<Source>> &options)
    -> void {
  assert(document.is_object());
  document.clear();
  document.assign(format::type, type);
  document.assign(format::encoding, encoding);
  document.assign(format::options, options);
}

template <typename Source>
auto make_integer_encoding(
    sourcemeta::jsontoolkit::JSON<Source> &document, const std::string encoding,
    const std::map<Source, sourcemeta::jsontoolkit::JSON<Source>> &options)
    -> void {
  return make_encoding(document, format::types::integer, encoding, options);
}

} // namespace sourcemeta::jsonbinpack::mapper

#endif
