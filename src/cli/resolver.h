#ifndef SOURCEMETA_JSONBINPACK_CLI_RESOLVER_H_
#define SOURCEMETA_JSONBINPACK_CLI_RESOLVER_H_

#include <sourcemeta/jsontoolkit/json.h>

#include <future>      // std::promise, std::future
#include <optional>    // std::optional
#include <string_view> // std::string_view

namespace sourcemeta::jsonbinpack::cli {

auto resolver(std::string_view identifier)
    -> std::future<std::optional<sourcemeta::jsontoolkit::JSON>>;

} // namespace sourcemeta::jsonbinpack::cli

#endif
