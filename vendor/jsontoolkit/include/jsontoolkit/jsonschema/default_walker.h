#ifndef JSONTOOLKIT_JSONSCHEMA_DEFAULT_WALKER_H_
#define JSONTOOLKIT_JSONSCHEMA_DEFAULT_WALKER_H_

#include <jsontoolkit/jsonschema/walker.h>

namespace sourcemeta::jsontoolkit {

// A stub walker that doesn't walk
auto schema_walker_none(const std::string &,
                        const std::unordered_map<std::string, bool> &)
    -> sourcemeta::jsontoolkit::schema_walker_strategy_t;

auto default_schema_walker(
    const std::string &keyword,
    const std::unordered_map<std::string, bool> &vocabularies)
    -> sourcemeta::jsontoolkit::schema_walker_strategy_t;

} // namespace sourcemeta::jsontoolkit

#endif
