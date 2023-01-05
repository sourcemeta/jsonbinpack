#ifndef JSONTOOLKIT_JSONSCHEMA_WALKER_H_
#define JSONTOOLKIT_JSONSCHEMA_WALKER_H_

#include <functional>    // std::function
#include <string>        // std::string
#include <unordered_map> // std::unordered_map

namespace sourcemeta::jsontoolkit {

#if defined(__GNUC__)
#pragma GCC diagnostic push
// For some strang reason, GCC on Debian 11 believes that a member of
// an enum class (which is namespaced by definition), can shadow an
// alias defined even on a different namespace.
#pragma GCC diagnostic ignored "-Wshadow"
enum class schema_walker_strategy_t {
  None,
  Value,
  Elements,
  Members,
  ValueOrElements,
  ElementsOrMembers
};
#pragma GCC diagnostic pop
#endif

// Take a keyword + vocabularies in use and guide subschema walking
using schema_walker_t = std::function<schema_walker_strategy_t(
    const std::string &, const std::unordered_map<std::string, bool> &)>;

enum class schema_walker_type_t { Deep, Flat };

} // namespace sourcemeta::jsontoolkit

#endif
