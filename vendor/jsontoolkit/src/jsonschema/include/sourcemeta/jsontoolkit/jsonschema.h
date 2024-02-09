#ifndef SOURCEMETA_JSONTOOLKIT_JSONSCHEMA_H_
#define SOURCEMETA_JSONTOOLKIT_JSONSCHEMA_H_

#if defined(__EMSCRIPTEN__) || defined(__Unikraft__)
#define SOURCEMETA_JSONTOOLKIT_JSONSCHEMA_EXPORT
#else
#include "jsonschema_export.h"
#endif

#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema_anchor.h>
#include <sourcemeta/jsontoolkit/jsonschema_bundle.h>
#include <sourcemeta/jsontoolkit/jsonschema_error.h>
#include <sourcemeta/jsontoolkit/jsonschema_reference.h>
#include <sourcemeta/jsontoolkit/jsonschema_resolver.h>
#include <sourcemeta/jsontoolkit/jsonschema_transform_bundle.h>
#include <sourcemeta/jsontoolkit/jsonschema_transform_rule.h>
#include <sourcemeta/jsontoolkit/jsonschema_transformer.h>
#include <sourcemeta/jsontoolkit/jsonschema_walker.h>

#include <future>   // std::future
#include <map>      // std::map
#include <optional> // std::optional
#include <string>   // std::string

/// @defgroup jsonschema JSON Schema
/// @brief A set of JSON Schema utilities across draft versions.
///
/// This functionality is included as follows:
///
/// ```cpp
/// #include <sourcemeta/jsontoolkit/jsonschema.h>
/// ```
///
/// Older JSON Schema versions might not be supported, but older JSON Schema
/// documents can be automatically upgraded using a tool like
/// [Alterschema](https://github.com/sourcemeta/alterschema).

namespace sourcemeta::jsontoolkit {

/// @ingroup jsonschema
///
/// This function returns true if the given JSON instance is of a
/// schema-compatible type: an object or a boolean. For example:
///
/// ```cpp
/// #include <sourcemeta/jsontoolkit/json.h>
/// #include <sourcemeta/jsontoolkit/jsonschema.h>
/// #include <cassert>
///
/// const sourcemeta::jsontoolkit::JSON document{true};
/// assert(sourcemeta::jsontoolkit::is_schema(document));
/// ```
SOURCEMETA_JSONTOOLKIT_JSONSCHEMA_EXPORT
auto is_schema(const JSON &schema) -> bool;

/// @ingroup jsonschema
///
/// This function returns the URI identifier of the given schema, if any. For
/// example:
///
/// ```cpp
/// #include <sourcemeta/jsontoolkit/json.h>
/// #include <sourcemeta/jsontoolkit/jsonschema.h>
/// #include <cassert>
///
/// const sourcemeta::jsontoolkit::JSON document =
///     sourcemeta::jsontoolkit::parse(R"JSON({
///   "$schema": "https://json-schema.org/draft/2020-12/schema",
///   "$id": "https://sourcemeta.com/example-schema"
/// })JSON");
///
/// std::optional<std::string> id{sourcemeta::jsontoolkit::id(
///   document, sourcemeta::jsontoolkit::official_resolver).get()};
/// assert(id.has_value());
/// assert(id.value() == "https://sourcemeta.com/example-schema");
/// ```
SOURCEMETA_JSONTOOLKIT_JSONSCHEMA_EXPORT
auto id(const JSON &schema, const SchemaResolver &resolver,
        const std::optional<std::string> &default_dialect = std::nullopt,
        const std::optional<std::string> &default_id = std::nullopt)
    -> std::future<std::optional<std::string>>;

/// @ingroup jsonschema
///
/// A shortcut to sourcemeta::jsontoolkit::id if you know the base dialect of
/// the schema.
SOURCEMETA_JSONTOOLKIT_JSONSCHEMA_EXPORT
auto id(const JSON &schema, const std::string &base_dialect,
        const std::optional<std::string> &default_id = std::nullopt)
    -> std::optional<std::string>;

/// @ingroup jsonschema
///
/// Get the dialect URI that corresponds to a JSON Schema instance.
/// The result is empty if the dialect cannot be determined. For example:
///
/// ```cpp
/// #include <sourcemeta/jsontoolkit/json.h>
/// #include <sourcemeta/jsontoolkit/jsonschema.h>
/// #include <cassert>
///
/// const sourcemeta::jsontoolkit::JSON document =
///   sourcemeta::jsontoolkit::parse(R"JSON({
///   "$schema": "https://json-schema.org/draft/2020-12/schema",
///   "type": "object"
/// })JSON");
///
/// const std::optional<std::string>
///   dialect{sourcemeta::jsontoolkit::dialect(document)};
/// assert(dialect.has_value());
/// assert(dialect.value() ==
///   "https://json-schema.org/draft/2020-12/schema");
/// ```
SOURCEMETA_JSONTOOLKIT_JSONSCHEMA_EXPORT
auto dialect(const JSON &schema,
             const std::optional<std::string> &default_dialect = std::nullopt)
    -> std::optional<std::string>;

/// @ingroup jsonschema
///
/// Get the URI of the base dialect that applies to the given schema. If you set
/// a default dialect URI, this will be used if the given schema does not
/// declare the `$schema` keyword. The result of this function is unset
/// if its base dialect could not be determined. For example:
///
/// ```cpp
/// #include <sourcemeta/jsontoolkit/json.h>
/// #include <sourcemeta/jsontoolkit/jsonschema.h>
/// #include <cassert>
///
/// const sourcemeta::jsontoolkit::JSON document =
///   sourcemeta::jsontoolkit::parse(R"JSON({
///   "$schema": "https://json-schema.org/draft/2020-12/schema",
///   "type": "object"
/// })JSON");
///
/// const std::optional<std::string> base_dialect{
///   sourcemeta::jsontoolkit::base_dialect(
///     document, sourcemeta::jsontoolkit::official_resolver).get()};
///
/// assert(base_dialect.has_value());
/// assert(base_dialect.value() ==
/// "https://json-schema.org/draft/2020-12/schema");
/// ```
SOURCEMETA_JSONTOOLKIT_JSONSCHEMA_EXPORT
auto base_dialect(const JSON &schema, const SchemaResolver &resolver,
                  const std::optional<std::string> &default_dialect =
                      std::nullopt) -> std::future<std::optional<std::string>>;

/// @ingroup jsonschema
///
/// List the vocabularies that a specific schema makes use of. If you set a
/// default dialect URI, this will be used if the given schema does not
/// declare the
/// `$schema` keyword. The resulting map values are set to `true` or `false`
/// depending on whether the corresponding vocabulary is required or optional,
/// respectively. For example:
///
/// ```cpp
/// #include <sourcemeta/jsontoolkit/json.h>
/// #include <sourcemeta/jsontoolkit/jsonschema.h>
/// #include <cassert>
///
/// const sourcemeta::jsontoolkit::JSON document =
///   sourcemeta::jsontoolkit::parse(R"JSON({
///   "$schema": "https://json-schema.org/draft/2020-12/schema",
///   "type": "object"
/// })JSON");
///
/// const std::map<std::string, bool> vocabularies{
///   sourcemeta::jsontoolkit::vocabularies(
///     document, sourcemeta::jsontoolkit::official_resolver).get()};
///
/// assert(vocabularies.at("https://json-schema.org/draft/2020-12/vocab/core"));
/// assert(vocabularies.at("https://json-schema.org/draft/2020-12/vocab/applicator"));
/// assert(vocabularies.at("https://json-schema.org/draft/2020-12/vocab/unevaluated"));
/// assert(vocabularies.at("https://json-schema.org/draft/2020-12/vocab/validation"));
/// assert(vocabularies.at("https://json-schema.org/draft/2020-12/vocab/meta-data"));
/// assert(vocabularies.at("https://json-schema.org/draft/2020-12/vocab/format-annotation"));
/// assert(vocabularies.at("https://json-schema.org/draft/2020-12/vocab/content"));
/// ```
SOURCEMETA_JSONTOOLKIT_JSONSCHEMA_EXPORT
auto vocabularies(const JSON &schema, const SchemaResolver &resolver,
                  const std::optional<std::string> &default_dialect =
                      std::nullopt) -> std::future<std::map<std::string, bool>>;

/// @ingroup jsonschema
///
/// A shortcut to sourcemeta::jsontoolkit::vocabularies based on the base
/// dialect and dialect URI.
SOURCEMETA_JSONTOOLKIT_JSONSCHEMA_EXPORT
auto vocabularies(const SchemaResolver &resolver,
                  const std::string &base_dialect, const std::string &dialect)
    -> std::future<std::map<std::string, bool>>;

} // namespace sourcemeta::jsontoolkit

#endif
