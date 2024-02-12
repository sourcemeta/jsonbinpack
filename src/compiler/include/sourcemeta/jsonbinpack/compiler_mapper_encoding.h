#ifndef SOURCEMETA_JSONBINPACK_COMPILER_MAPPER_ENCODING_H_
#define SOURCEMETA_JSONBINPACK_COMPILER_MAPPER_ENCODING_H_

#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

#include <future>   // std::future
#include <optional> // std::optional
#include <string>   // std::string

namespace sourcemeta::jsonbinpack::mapper {

namespace keywords {
const std::string version{"$schema"};
const std::string name{"name"};
const std::string options{"options"};
} // namespace keywords

auto is_encoding(const sourcemeta::jsontoolkit::JSON &document) -> bool;

auto make_encoding(sourcemeta::jsontoolkit::SchemaTransformer &document,
                   const std::string &encoding,
                   const sourcemeta::jsontoolkit::JSON &options) -> void;

auto resolver(const std::string &identifier)
    -> std::future<std::optional<sourcemeta::jsontoolkit::JSON>>;

} // namespace sourcemeta::jsonbinpack::mapper

#endif
