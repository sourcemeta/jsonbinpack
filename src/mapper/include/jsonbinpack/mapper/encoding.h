#ifndef SOURCEMETA_JSONBINPACK_MAPPER_ENCODING_H_
#define SOURCEMETA_JSONBINPACK_MAPPER_ENCODING_H_

#include <jsontoolkit/json.h>

#include <future>   // std::future
#include <optional> // std::optional
#include <string>   // std::string

namespace sourcemeta::jsonbinpack::mapper {

const std::string V1{"https://www.jsonbinpack.org/schemas/encoding/v1.json"};

namespace keywords {
const std::string version{"$schema"};
const std::string encoding{"encoding"};
const std::string options{"options"};
} // namespace keywords

auto is_encoding(const sourcemeta::jsontoolkit::Value &document) -> bool;

auto make_encoding(sourcemeta::jsontoolkit::JSON &document,
                   sourcemeta::jsontoolkit::Value &value,
                   const std::string &encoding,
                   const sourcemeta::jsontoolkit::Value &options) -> void;

inline auto make_encoding(sourcemeta::jsontoolkit::JSON &document,
                          const std::string &encoding,
                          const sourcemeta::jsontoolkit::Value &options)
    -> void {
  return make_encoding(document, document, encoding, options);
}

auto resolver(const std::string &identifier)
    -> std::future<std::optional<sourcemeta::jsontoolkit::JSON>>;

} // namespace sourcemeta::jsonbinpack::mapper

#endif
