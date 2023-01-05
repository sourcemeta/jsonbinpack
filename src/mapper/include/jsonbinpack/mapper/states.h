#ifndef SOURCEMETA_JSONBINPACK_MAPPER_STATES_H_
#define SOURCEMETA_JSONBINPACK_MAPPER_STATES_H_

#include <jsontoolkit/json.h>
#include <optional>      // std::optional
#include <unordered_map> // std::unordered_map

namespace sourcemeta::jsonbinpack::mapper::states {

// No value means infinite
auto integer(const sourcemeta::jsontoolkit::Value &schema,
             const std::unordered_map<std::string, bool> &vocabularies)
    -> std::optional<std::vector<sourcemeta::jsontoolkit::JSON>>;

} // namespace sourcemeta::jsonbinpack::mapper::states

#endif
