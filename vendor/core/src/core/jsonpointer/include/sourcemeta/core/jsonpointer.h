#ifndef SOURCEMETA_CORE_JSONPOINTER_H_
#define SOURCEMETA_CORE_JSONPOINTER_H_

#ifndef SOURCEMETA_CORE_JSONPOINTER_EXPORT
#include <sourcemeta/core/jsonpointer_export.h>
#endif

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/uri.h>

#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/jsonpointer_error.h>
#include <sourcemeta/core/jsonpointer_pointer.h>
#include <sourcemeta/core/jsonpointer_position.h>
#include <sourcemeta/core/jsonpointer_proxy.h>
#include <sourcemeta/core/jsonpointer_subpointer_walker.h>
#include <sourcemeta/core/jsonpointer_template.h>
#include <sourcemeta/core/jsonpointer_walker.h>

#include <functional> // std::reference_wrapper
#include <memory>     // std::allocator
#include <ostream>    // std::basic_ostream
#include <string>     // std::basic_string

/// @defgroup jsonpointer JSON Pointer
/// @brief An growing implementation of RFC 6901 JSON Pointer.
///
/// This functionality is included as follows:
///
/// ```cpp
/// #include <sourcemeta/core/jsonpointer.h>
/// ```

namespace sourcemeta::core {

/// @ingroup jsonpointer
using Pointer = GenericPointer<JSON::String, PropertyHashJSON<JSON::String>>;

/// @ingroup jsonpointer
using WeakPointer = GenericPointer<std::reference_wrapper<const std::string>,
                                   PropertyHashJSON<JSON::String>>;

/// @ingroup jsonpointer
/// A global constant instance of the empty JSON Pointer.
const Pointer empty_pointer;

/// @ingroup jsonpointer
/// A global constant instance of the empty JSON WeakPointer.
const WeakPointer empty_weak_pointer;

/// @ingroup jsonpointer
/// A JSON Pointer with unresolved wildcards
using PointerTemplate = GenericPointerTemplate<Pointer>;

/// @ingroup jsonpointer
using PointerProxy = GenericPointerProxy<Pointer>;

/// @ingroup jsonpointer
/// Get a value from a JSON document using a JSON Pointer (`const` overload).
///
/// ```cpp
/// #include <sourcemeta/core/json.h>
/// #include <sourcemeta/core/jsonpointer.h>
/// #include <cassert>
/// #include <sstream>
///
/// std::istringstream stream{"[ { \"foo\": 1 }, { \"bar\": 2 } ]"};
/// const sourcemeta::core::JSON document =
///   sourcemeta::core::parse_json(stream);
///
/// const sourcemeta::core::Pointer pointer{1, "bar"};
/// const sourcemeta::core::JSON &value{
///   sourcemeta::core::get(document, pointer)};
/// assert(value.is_integer());
/// assert(value.to_integer() == 2);
/// ```
SOURCEMETA_CORE_JSONPOINTER_EXPORT
auto get(const JSON &document, const Pointer &pointer) -> const JSON &;

/// @ingroup jsonpointer
/// Get a value from a JSON document using a JSON WeakPointer (`const`
/// overload).
///
/// ```cpp
/// #include <sourcemeta/core/json.h>
/// #include <sourcemeta/core/jsonpointer.h>
/// #include <cassert>
/// #include <sstream>
///
/// std::istringstream stream{"[ { \"foo\": 1 }, { \"bar\": 2 } ]"};
/// const sourcemeta::core::JSON document =
///   sourcemeta::core::parse_json(stream);
///
/// const std::string bar = "bar";
/// const sourcemeta::core::WeakPointer pointer{1, std::cref(bar)};
/// const sourcemeta::core::JSON &value{
///   sourcemeta::core::get(document, pointer)};
/// assert(value.is_integer());
/// assert(value.to_integer() == 2);
/// ```
SOURCEMETA_CORE_JSONPOINTER_EXPORT
auto get(const JSON &document, const WeakPointer &pointer) -> const JSON &;

/// @ingroup jsonpointer
/// Get a value from a JSON document using a Pointer, returning an optional that
/// is not set if the path does not exist in the document. For example:
///
/// ```cpp
/// #include <sourcemeta/core/json.h>
/// #include <sourcemeta/core/jsonpointer.h>
/// #include <cassert>
/// #include <sstream>
///
/// std::istringstream stream{"[ { \"foo\": 1 }, { \"bar\": 2 } ]"};
/// const auto document{sourcemeta::core::parse_json(stream)};
/// const sourcemeta::core::Pointer pointer{1, "bar"};
/// const auto result{sourcemeta::core::try_get(document, pointer)};
/// assert(result);
/// assert(*result == document.at(1).at("bar"));
/// ```
SOURCEMETA_CORE_JSONPOINTER_EXPORT
auto try_get(const JSON &document, const Pointer &pointer) -> const JSON *;

/// @ingroup jsonpointer
/// Get a value from a JSON document using a WeakPointer, returning an optional
/// that is not set if the path does not exist in the document. For example:
///
/// ```cpp
/// #include <sourcemeta/core/json.h>
/// #include <sourcemeta/core/jsonpointer.h>
/// #include <cassert>
/// #include <sstream>
///
/// std::istringstream stream{"[ { \"foo\": 1 }, { \"bar\": 2 } ]"};
/// const auto document{sourcemeta::core::parse_json(stream)};
/// const std::string bar = "bar";
/// const sourcemeta::core::WeakPointer pointer{1, std::cref(bar)};
/// const auto result{sourcemeta::core::try_get(document, pointer)};
/// assert(result);
/// assert(*result == document.at(1).at("bar"));
/// ```
SOURCEMETA_CORE_JSONPOINTER_EXPORT
auto try_get(const JSON &document, const WeakPointer &pointer) -> const JSON *;

/// @ingroup jsonpointer
/// Get a value from a JSON document using a JSON Pointer (non-`const`
/// overload).
///
/// ```cpp
/// #include <sourcemeta/core/json.h>
/// #include <sourcemeta/core/jsonpointer.h>
/// #include <cassert>
/// #include <sstream>
///
/// std::istringstream stream{"[ { \"foo\": 1 }, { \"bar\": 2 } ]"};
/// sourcemeta::core::JSON document =
///   sourcemeta::core::parse_json(stream);
/// assert(document.at("foo").to_integer() == 1);
///
/// const sourcemeta::core::Pointer pointer{1, "bar"};
/// sourcemeta::core::JSON &value{
///   sourcemeta::core::get(document, pointer)};
/// assert(value.is_integer());
/// assert(value.to_integer() == 2);
/// ```
SOURCEMETA_CORE_JSONPOINTER_EXPORT
auto get(JSON &document, const Pointer &pointer) -> JSON &;

/// @ingroup jsonpointer
/// Get a value from a JSON document using a JSON Pointer token (`const`
/// overload).
///
/// ```cpp
/// #include <sourcemeta/core/json.h>
/// #include <sourcemeta/core/jsonpointer.h>
/// #include <cassert>
/// #include <sstream>
///
/// std::istringstream stream{"{ \"foo\": 1 }"};
/// const sourcemeta::core::JSON document =
///   sourcemeta::core::parse_json(stream);
///
/// const sourcemeta::core::JSON &value{
///   sourcemeta::core::get(document,
///   sourcemeta::core::Pointer{"foo"})};
/// assert(value.is_integer());
/// assert(value.to_integer() == 1);
/// ```
SOURCEMETA_CORE_JSONPOINTER_EXPORT
auto get(const JSON &document, const Pointer::Token &token) -> const JSON &;

/// @ingroup jsonpointer
/// Get a value from a JSON document using a JSON WeakPointer token (`const`
/// overload).
///
/// ```cpp
/// #include <sourcemeta/core/json.h>
/// #include <sourcemeta/core/jsonpointer.h>
/// #include <cassert>
/// #include <sstream>
///
/// std::istringstream stream{"{ \"foo\": 1 }"};
/// const sourcemeta::core::JSON document =
///   sourcemeta::core::parse_json(stream);
///
/// const std::string foo = "foo";
/// const sourcemeta::core::JSON &value{
///   sourcemeta::core::get(document,
///   sourcemeta::core::WeakPointer{std::cref(foo)})};
/// assert(value.is_integer());
/// assert(value.to_integer() == 1);
/// ```
SOURCEMETA_CORE_JSONPOINTER_EXPORT
auto get(const JSON &document, const WeakPointer::Token &token) -> const JSON &;

/// @ingroup jsonpointer
/// Get a value from a JSON document using a JSON Pointer token (non-`const`
/// overload).
///
/// ```cpp
/// #include <sourcemeta/core/json.h>
/// #include <sourcemeta/core/jsonpointer.h>
/// #include <cassert>
/// #include <sstream>
///
/// std::istringstream stream{"{ \"foo\": 1 }"};
/// sourcemeta::core::JSON document =
///   sourcemeta::core::parse_json(stream);
///
/// sourcemeta::core::JSON &value{
///   sourcemeta::core::get(document, "bar")};
/// assert(value.is_integer());
/// assert(value.to_integer() == 2);
/// ```
SOURCEMETA_CORE_JSONPOINTER_EXPORT
auto get(JSON &document, const Pointer::Token &token) -> JSON &;

/// @ingroup jsonpointer
/// Set a value in a JSON document using a JSON Pointer (`const` overload).
///
/// If the last token of the JSON Pointer is the constant `-` and the tail
/// instance is an array, then the operation is equivalent to
/// `sourcemeta::core::JSON::push_back`.
///
/// ```cpp
/// #include <sourcemeta/core/json.h>
/// #include <sourcemeta/core/jsonpointer.h>
/// #include <cassert>
/// #include <sstream>
///
/// std::istringstream stream{"{ \"foo\": 1 }"};
/// sourcemeta::core::JSON document =
///   sourcemeta::core::parse_json(stream);
/// assert(document.at("foo").to_integer() == 1);
///
/// const sourcemeta::core::Pointer pointer{"foo"};
/// const sourcemeta::core::JSON value{2};
/// sourcemeta::core::set(document, pointer, value);
/// assert(document.at("foo").to_integer() == 2);
/// ```
SOURCEMETA_CORE_JSONPOINTER_EXPORT
auto set(JSON &document, const Pointer &pointer, const JSON &value) -> void;

/// @ingroup jsonpointer
/// Set a value in a JSON document using a JSON Pointer (non-`const` overload).
///
/// If the last token of the JSON Pointer is the constant `-` and the tail
/// instance is an array, then the operation is equivalent to
/// `sourcemeta::core::JSON::push_back`.
///
/// ```cpp
/// #include <sourcemeta/core/json.h>
/// #include <sourcemeta/core/jsonpointer.h>
/// #include <cassert>
/// #include <sstream>
///
/// std::istringstream stream{"{ \"foo\": 1 }"};
/// sourcemeta::core::JSON document =
///   sourcemeta::core::parse_json(stream);
///
/// const sourcemeta::core::Pointer pointer{"foo"};
/// sourcemeta::core::set(document, pointer,
///   sourcemeta::core::JSON{2});
/// assert(document.at("foo").to_integer() == 2);
/// ```
SOURCEMETA_CORE_JSONPOINTER_EXPORT
auto set(JSON &document, const Pointer &pointer, JSON &&value) -> void;

/// @ingroup jsonpointer
/// Create a JSON Pointer from a JSON string value. For example:
///
/// ```cpp
/// #include <sourcemeta/core/json.h>
/// #include <sourcemeta/core/jsonpointer.h>
/// #include <cassert>
///
/// const sourcemeta::core::JSON document{"/foo/bar/0"};
/// assert(document.is_string());
/// const sourcemeta::core::Pointer pointer =
///   sourcemeta::core::to_pointer(document);
/// assert(pointer.size() == 3);
/// ```
SOURCEMETA_CORE_JSONPOINTER_EXPORT
auto to_pointer(const JSON &document) -> Pointer;

/// @ingroup jsonpointer
/// Create a JSON Pointer from a standard C++ string. For example:
///
/// ```cpp
/// #include <sourcemeta/core/jsonpointer.h>
/// #include <cassert>
///
/// const sourcemeta::core::Pointer pointer =
///   sourcemeta::core::to_pointer("/foo/bar/0");
/// assert(pointer.size() == 3);
/// ```
SOURCEMETA_CORE_JSONPOINTER_EXPORT
auto to_pointer(const std::basic_string<JSON::Char, JSON::CharTraits,
                                        std::allocator<JSON::Char>> &input)
    -> Pointer;

/// @ingroup jsonpointer
/// Convert a JSON WeakPointer into a JSON Pointer. For example:
///
/// ```cpp
/// #include <sourcemeta/core/jsonpointer.h>
/// #include <cassert>
///
/// const std::string foo = "foo";
/// const sourcemeta::core::WeakPointer pointer{std::cref(foo)};
/// const sourcemeta::core::Pointer result{
///   sourcemeta::core::to_pointer(pointer)}:
/// assert(pointer.size() == 1);
/// assert(pointer.at(0).is_property());
/// assert(pointer.at(0).to_property() == "foo");
/// ```
SOURCEMETA_CORE_JSONPOINTER_EXPORT
auto to_pointer(const WeakPointer &pointer) -> Pointer;

/// @ingroup jsonpointer
///
/// Stringify the input JSON Pointer into a given C++ standard output stream.
/// For example:
///
/// ```cpp
/// #include <sourcemeta/core/jsonpointer.h>
/// #include <iostream>
/// #include <sstream>
///
/// const sourcemeta::core::Pointer pointer{"foo"};
/// std::ostringstream stream;
/// sourcemeta::core::stringify(pointer, stream);
/// std::cout << stream.str() << std::endl;
/// ```
SOURCEMETA_CORE_JSONPOINTER_EXPORT
auto stringify(const Pointer &pointer,
               std::basic_ostream<JSON::Char, JSON::CharTraits> &stream)
    -> void;

/// @ingroup jsonpointer
///
/// Stringify the input JSON WeakPointer into a given C++ standard output
/// stream. For example:
///
/// ```cpp
/// #include <sourcemeta/core/jsonpointer.h>
/// #include <iostream>
/// #include <sstream>
///
/// const std::string foo = "foo";
/// const sourcemeta::core::WeakPointer pointer{std::cref(foo)};
/// std::ostringstream stream;
/// sourcemeta::core::stringify(pointer, stream);
/// std::cout << stream.str() << std::endl;
/// ```
SOURCEMETA_CORE_JSONPOINTER_EXPORT
auto stringify(const WeakPointer &pointer,
               std::basic_ostream<JSON::Char, JSON::CharTraits> &stream)
    -> void;

/// @ingroup jsonpointer
///
/// Stringify the input JSON Pointer template into a given C++ standard output
/// stream. For example:
///
/// ```cpp
/// #include <sourcemeta/core/jsonpointer.h>
/// #include <iostream>
/// #include <sstream>
///
/// const sourcemeta::core::Pointer base{"foo", "bar"};
/// const sourcemeta::core::PointerTemplate pointer{base};
/// std::ostringstream stream;
/// sourcemeta::core::stringify(pointer, stream);
/// std::cout << stream.str() << std::endl;
/// ```
SOURCEMETA_CORE_JSONPOINTER_EXPORT
auto stringify(const PointerTemplate &pointer,
               std::basic_ostream<JSON::Char, JSON::CharTraits> &stream)
    -> void;

/// @ingroup jsonpointer
///
/// Stringify the input JSON Pointer into a C++ standard string. For example:
///
/// ```cpp
/// #include <sourcemeta/core/jsonpointer.h>
/// #include <string>
/// #include <iostream>
///
/// const sourcemeta::core::Pointer pointer{"foo"};
/// const std::string result{sourcemeta::core::to_string(pointer)};
/// std::cout << result << std::endl;
/// ```
SOURCEMETA_CORE_JSONPOINTER_EXPORT
auto to_string(const Pointer &pointer)
    -> std::basic_string<JSON::Char, JSON::CharTraits,
                         std::allocator<JSON::Char>>;

/// @ingroup jsonpointer
///
/// Stringify the input JSON WeakPointer into a C++ standard string. For
/// example:
///
/// ```cpp
/// #include <sourcemeta/core/jsonpointer.h>
/// #include <string>
/// #include <iostream>
///
/// const std::string foo = "foo";
/// const sourcemeta::core::WeakPointer pointer{foo};
/// const std::string result{sourcemeta::core::to_string(pointer)};
/// std::cout << result << std::endl;
/// ```
SOURCEMETA_CORE_JSONPOINTER_EXPORT
auto to_string(const WeakPointer &pointer)
    -> std::basic_string<JSON::Char, JSON::CharTraits,
                         std::allocator<JSON::Char>>;

/// @ingroup jsonpointer
///
/// Stringify the input JSON Pointer into a properly escaped URI fragment. For
/// example:
///
/// ```cpp
/// #include <sourcemeta/core/uri.h>
/// #include <sourcemeta/core/jsonpointer.h>
///
/// #include <assert>
///
/// const sourcemeta::core::Pointer pointer{"foo"};
/// const sourcemeta::core::URI fragment{
///   sourcemeta::core::to_uri(pointer)};
/// assert(fragment.recompose() == "#/foo");
/// ```
SOURCEMETA_CORE_JSONPOINTER_EXPORT
auto to_uri(const Pointer &pointer) -> URI;

/// @ingroup jsonpointer
///
/// Stringify the input JSON Pointer into a properly escaped URI fragment
/// alongside a base URI. For example:
///
/// ```cpp
/// #include <sourcemeta/core/uri.h>
/// #include <sourcemeta/core/jsonpointer.h>
///
/// #include <assert>
///
/// const sourcemeta::core::Pointer pointer{"foo"};
/// const sourcemeta::core::URI base{"https://www.example.com"};
/// const sourcemeta::core::URI fragment{
///   sourcemeta::core::to_uri(pointer, base)};
/// assert(fragment.recompose() == "https://example.com#/foo");
/// ```
SOURCEMETA_CORE_JSONPOINTER_EXPORT
auto to_uri(const Pointer &pointer, const URI &base) -> URI;

/// @ingroup jsonpointer
///
/// Walk over every element of a JSON document, top-down, using JSON Pointers.
/// For example:
///
/// ```cpp
/// #include <sourcemeta/core/json.h>
/// #include <sourcemeta/core/jsonpointer.h>
/// #include <cassert>
/// #include <vector>
///
/// const sourcemeta::core::JSON document =
///   sourcemeta::core::parse_json("[ 1, 2, 3 ]");
/// std::vector<sourcemeta::core::Pointer> subpointers;
///
/// for (const auto &subpointer :
///   sourcemeta::core::PointerWalker{document}) {
///   subpointers.push_back(subpointer);
/// }
///
/// assert(subpointers.size() == 4);
/// assert(subpointers.at(0) == sourcemeta::core::Pointer{});
/// assert(subpointers.at(1) == sourcemeta::core::Pointer{0});
/// assert(subpointers.at(2) == sourcemeta::core::Pointer{1});
/// assert(subpointers.at(3) == sourcemeta::core::Pointer{2});
/// ```
using PointerWalker = GenericPointerWalker<Pointer>;

/// @ingroup jsonpointer
///
/// Walk over every subpointer of a JSON Pointer, from the current pointer down
/// to the empty pointer. For example:
///
/// ```cpp
/// #include <sourcemeta/core/json.h>
/// #include <sourcemeta/core/jsonpointer.h>
/// #include <cassert>
/// #include <vector>
///
/// const sourcemeta::core::Pointer pointer{"foo", "bar"};
/// std::vector<sourcemeta::core::Pointer> subpointers;
///
/// for (const auto &subpointer :
///   sourcemeta::core::SubPointerWalker{pointer}) {
///   subpointers.push_back(subpointer);
/// }
///
/// assert(subpointers.size() == 3);
/// assert(subpointers.at(0) == sourcemeta::core::Pointer{"foo", "bar"});
/// assert(subpointers.at(1) == sourcemeta::core::Pointer{"foo"});
/// assert(subpointers.at(2) == sourcemeta::core::Pointer{});
/// ```
using SubPointerWalker = GenericSubPointerWalker<Pointer>;

} // namespace sourcemeta::core

#endif
