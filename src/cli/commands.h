#ifndef SOURCEMETA_JSONBINPACK_CLI_COMMANDS_H_
#define SOURCEMETA_JSONBINPACK_CLI_COMMANDS_H_

#include <string> // std::string

namespace sourcemeta::jsonbinpack::cli {
auto help(const std::string &program) -> int;
auto version() -> int;
auto canonicalize(const std::string &schema_path) -> int;
} // namespace sourcemeta::jsonbinpack::cli

#endif
