#ifndef SOURCEMETA_JSONBINPACK_COMPILER_MAPPER_STATES_H_
#define SOURCEMETA_JSONBINPACK_COMPILER_MAPPER_STATES_H_

#include <sourcemeta/jsontoolkit/json.h>

#include <optional> // std::optional
#include <set>      // std::set
#include <vector>   // std::vector

namespace sourcemeta::jsonbinpack::mapper::states {

// No value means infinite
auto integer(const sourcemeta::jsontoolkit::JSON &schema,
             const std::set<std::string> &vocabularies)
    -> std::optional<std::vector<sourcemeta::jsontoolkit::JSON>>;

} // namespace sourcemeta::jsonbinpack::mapper::states

#endif
