#ifndef JSONTOOLKIT_JSONSCHEMA_H_
#define JSONTOOLKIT_JSONSCHEMA_H_

#include <jsontoolkit/json.h>
#include <jsontoolkit/jsonschema/default_resolver.h>
#include <jsontoolkit/jsonschema/default_walker.h>
#include <jsontoolkit/jsonschema/resolver.h>
#include <jsontoolkit/jsonschema/walker.h>

#include <future>        // std::promise, std::future
#include <optional>      // std::optional
#include <stdexcept>     // std::invalid_argument
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace sourcemeta::jsontoolkit {

auto is_schema(const Value &schema) -> bool;
auto id(const Value &schema) -> std::optional<std::string>;
auto metaschema(const Value &schema) -> std::optional<std::string>;
auto dialect(const Value &schema, const schema_resolver_t &resolver,
             const std::optional<std::string> &default_metaschema =
                 std::nullopt) -> std::future<std::optional<std::string>>;
auto vocabularies(
    const Value &schema, const schema_resolver_t &resolver,
    const std::optional<std::string> &default_metaschema = std::nullopt)
    -> std::future<std::unordered_map<std::string, bool>>;

// We inline the definition of this class in this file to avoid a circular
// dependency
template <typename ValueT> class SchemaWalker {
public:
  SchemaWalker(ValueT &input, const schema_walker_t &walker,
               const schema_resolver_t &resolver,
               const std::optional<std::string> &default_metaschema,
               const schema_walker_type_t type)
      : walker_type{type} {
    const std::optional<std::string> metaschema{
        sourcemeta::jsontoolkit::metaschema(input)};

    // If the given schema declares no metaschema and the user didn't
    // not pass a default, then there is nothing we can do. We know
    // the current schema is a subschema, but cannot walk any further.
    if (!metaschema.has_value() && !default_metaschema.has_value()) {
      if (this->walker_type != schema_walker_type_t::Flat) {
        this->subschemas.push_back(input);
      }
    } else {
      const std::string &effective_metaschema{metaschema.has_value()
                                                  ? metaschema.value()
                                                  : default_metaschema.value()};
      this->walk(input, walker, resolver, effective_metaschema, 0);
    }
  }

  inline auto begin() const -> decltype(auto) {
    return this->subschemas.begin();
  }
  inline auto end() const -> decltype(auto) { return this->subschemas.end(); }

  inline auto cbegin() const -> decltype(auto) {
    return this->subschemas.cbegin();
  }
  inline auto cend() const -> decltype(auto) { return this->subschemas.cend(); }

private:
  auto walk(ValueT &subschema, const schema_walker_t &walker,
            const schema_resolver_t &resolver, const std::string &metaschema,
            const std::size_t level) -> void {
    if (this->walker_type == schema_walker_type_t::Deep || level > 0) {
      this->subschemas.push_back(subschema);
    }

    // We can't recurse any further
    if (!is_object(subschema)) {
      return;
    } else if (this->walker_type == schema_walker_type_t::Flat && level > 0) {
      return;
    }

    // Recalculate the metaschema and its vocabularies at every step.
    // This is needed for correctly traversing through schemas that
    // contains subschemas that use different metaschemas/vocabularies.
    // This is often the case for bundled schemas.
    const std::optional<std::string> current_metaschema{
        sourcemeta::jsontoolkit::metaschema(subschema)};
    const std::string &new_metaschema{current_metaschema.has_value()
                                          ? current_metaschema.value()
                                          : metaschema};
    const std::unordered_map<std::string, bool> vocabularies{
        sourcemeta::jsontoolkit::vocabularies(subschema, resolver,
                                              new_metaschema)
            .get()};

    for (auto &pair : object_iterator(subschema)) {
      switch (walker(key(pair), vocabularies)) {
      case schema_walker_strategy_t::Value:
        this->walk_schema(value(pair), walker, resolver, new_metaschema, level);
        break;
      case schema_walker_strategy_t::Elements:
        this->walk_array(value(pair), walker, resolver, new_metaschema, level);
        break;
      case schema_walker_strategy_t::Members:
        this->walk_object(value(pair), walker, resolver, new_metaschema, level);
        break;
      case schema_walker_strategy_t::ValueOrElements:
        if (is_array(value(pair))) {
          this->walk_array(value(pair), walker, resolver, new_metaschema,
                           level);
        } else {
          this->walk_schema(value(pair), walker, resolver, new_metaschema,
                            level);
        }
        break;
      case schema_walker_strategy_t::ElementsOrMembers:
        if (is_array(value(pair))) {
          this->walk_array(value(pair), walker, resolver, new_metaschema,
                           level);
        } else {
          this->walk_object(value(pair), walker, resolver, new_metaschema,
                            level);
        }
        break;
      default:
        break;
      }
    }
  }

  auto walk_array(ValueT &array, const schema_walker_t &walker,
                  const schema_resolver_t &resolver,
                  const std::string &metaschema, const std::size_t level)
      -> void {
    if (is_array(array)) {
      for (auto &element : array_iterator(array)) {
        this->walk(element, walker, resolver, metaschema, level + 1);
      }
    }
  }

  auto walk_object(ValueT &object, const schema_walker_t &walker,
                   const schema_resolver_t &resolver,
                   const std::string &metaschema, const std::size_t level)
      -> void {
    if (is_object(object)) {
      for (auto &pair : object_iterator(object)) {
        this->walk(value(pair), walker, resolver, metaschema, level + 1);
      }
    }
  }

  auto walk_schema(ValueT &schema, const schema_walker_t &walker,
                   const schema_resolver_t &resolver,
                   const std::string &metaschema, const std::size_t level)
      -> void {
    if (is_object(schema) || is_boolean(schema)) {
      this->walk(schema, walker, resolver, metaschema, level + 1);
    }
  }

  std::vector<std::reference_wrapper<ValueT>> subschemas;
  const schema_walker_type_t walker_type;
};

auto subschema_iterator(
    const Value &schema, const schema_walker_t &walker,
    const schema_resolver_t &resolver,
    const std::optional<std::string> &default_metaschema = std::nullopt)
    -> SchemaWalker<std::remove_reference_t<decltype(schema)>>;

auto flat_subschema_iterator(
    const Value &schema, const schema_walker_t &walker,
    const schema_resolver_t &resolver,
    const std::optional<std::string> &default_metaschema = std::nullopt)
    -> SchemaWalker<std::remove_reference_t<decltype(schema)>>;

auto flat_subschema_iterator(
    Value &schema, const schema_walker_t &walker,
    const schema_resolver_t &resolver,
    const std::optional<std::string> &default_metaschema = std::nullopt)
    -> SchemaWalker<std::remove_reference_t<decltype(schema)>>;

} // namespace sourcemeta::jsontoolkit

#endif
