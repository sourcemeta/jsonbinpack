#ifndef SOURCEMETA_JSONBINPACK_CLI_RESOLVER_H_
#define SOURCEMETA_JSONBINPACK_CLI_RESOLVER_H_

#include <jsontoolkit/json.h>

#include <future>   // std::promise, std::future
#include <optional> // std::optional
#include <string>   // std::string

namespace sourcemeta::jsonbinpack::cli {

auto resolver(const std::string &identifier)
    -> std::future<std::optional<sourcemeta::jsontoolkit::JSON>>;

} // namespace sourcemeta::jsonbinpack::cli

#endif
