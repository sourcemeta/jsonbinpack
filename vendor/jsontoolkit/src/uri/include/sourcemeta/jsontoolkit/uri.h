#ifndef SOURCEMETA_JSONTOOLKIT_URI_H_
#define SOURCEMETA_JSONTOOLKIT_URI_H_

#ifndef SOURCEMETA_JSONTOOLKIT_URI_EXPORT
#include <sourcemeta/jsontoolkit/uri_export.h>
#endif

#include <sourcemeta/jsontoolkit/uri_error.h>

#include <cstdint>     // std::uint32_t
#include <istream>     // std::istream
#include <memory>      // std::unique_ptr
#include <optional>    // std::optional
#include <ostream>     // std::ostream
#include <span>        // std::span
#include <string>      // std::string
#include <string_view> // std::string_view
#include <vector>      // std::vector

/// @defgroup uri URI
/// @brief A RFC 3986 URI implementation based on `uriparser`.
///
/// This functionality is included as follows:
///
/// ```cpp
/// #include <sourcemeta/jsontoolkit/uri.h>
/// ```

namespace sourcemeta::jsontoolkit {

/// @ingroup uri
class SOURCEMETA_JSONTOOLKIT_URI_EXPORT URI {
public:
  // TODO: Add a constructor that takes a C++ input stream

  /// This constructor creates a URI from a string type. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/uri.h>
  ///
  /// const sourcemeta::jsontoolkit::URI uri{"https://www.sourcemeta.com"};
  /// ```
  URI(std::string input);

  /// This constructor creates a URI from a C++ input stream. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/uri.h>
  /// #include <sstream>
  ///
  /// std::istringstream input{"https://www.sourcemeta.com"};
  /// const sourcemeta::jsontoolkit::URI uri{input};
  /// ```
  URI(std::istream &input);

  /// Destructor
  ~URI();

  /// Copy constructor
  URI(const URI &other);

  /// Move constructor
  URI(URI &&other);

  /// Check if the URI is absolute. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/uri.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::URI uri{"https://www.sourcemeta.com"};
  /// assert(uri.is_absolute());
  /// ```
  [[nodiscard]] auto is_absolute() const noexcept -> bool;

  /// Check if the URI is a URN. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/uri.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::URI uri{"urn:example:schema"};
  /// assert(uri.is_urn());
  /// ```
  auto is_urn() const -> bool;

  /// Check if the URI is a tag as described by RFC 4151. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/uri.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::URI uri{"tag:yaml.org,2002:int"};
  /// assert(uri.is_tag());
  /// ```
  auto is_tag() const -> bool;

  /// Check if the URI has the `mailto` scheme. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/uri.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::URI uri{"mailto:joe@example.com"};
  /// assert(uri.is_mailto());
  /// ```
  auto is_mailto() const -> bool;

  /// Check if the URI only consists of a fragment. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/uri.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::URI uri{"#foo"};
  /// assert(uri.is_fragment_only());
  /// ```
  auto is_fragment_only() const -> bool;

  /// Check if the URI is relative. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/uri.h>
  /// #include <cassert>
  ///
  /// sourcemeta::jsontoolkit::URI uri{"./foo"};
  /// assert(uri.is_relative());
  /// ```
  auto is_relative() const -> bool;

  /// Check if the host is an ipv6 address. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/uri.h>
  /// #include <cassert>
  ///
  /// sourcemeta::jsontoolkit::URI uri{"http://[::1]"};
  /// assert(uri.is_ipv6());
  /// ```
  auto is_ipv6() const -> bool;

  /// Get the scheme part of the URI, if any. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/uri.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::URI uri{"https://www.sourcemeta.com"};
  /// assert(uri.scheme().has_value());
  /// assert(uri.scheme().value() == "https");
  /// ```
  [[nodiscard]] auto scheme() const -> std::optional<std::string_view>;

  /// Get the host part of the URI, if any. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/uri.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::URI uri{"https://www.sourcemeta.com"};
  /// assert(uri.host().has_value());
  /// assert(uri.host().value() == "sourcemeta.com");
  /// ```
  [[nodiscard]] auto host() const -> std::optional<std::string_view>;

  /// Get the port part of the URI, if any. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/uri.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::URI uri{"http://localhost:8000"};
  /// assert(uri.port().has_value());
  /// assert(uri.port().value() == 8000);
  /// ```
  [[nodiscard]] auto port() const -> std::optional<std::uint32_t>;

  /// Get the path part of the URI, if any. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/uri.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::URI
  /// uri{"https://www.sourcemeta.com/foo/bar"};
  /// assert(uri.path().has_value());
  /// assert(uri.path().value() == "/foo/bar");
  /// ```
  [[nodiscard]] auto path() const -> std::optional<std::string>;

  /// Set the path part of the URI. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/uri.h>
  /// #include <cassert>
  ///
  /// sourcemeta::jsontoolkit::URI uri{"https://www.sourcemeta.com"};
  /// const std::string path{"/foo/bar"};
  /// uri.path(path);
  /// assert(uri.path().has_value());
  /// assert(uri.path().value() == "/foo/bar");
  /// ```
  auto path(const std::string &path) -> URI &;

  /// Set the path part of the URI with move semantics. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/uri.h>
  /// #include <cassert>
  ///
  /// sourcemeta::jsontoolkit::URI uri{"https://www.sourcemeta.com"};
  /// std::string path{"/foo/bar"};
  /// uri.path(std::move(path));
  /// assert(uri.path().has_value());
  /// assert(uri.path().value() == "/foo/bar");
  auto path(std::string &&path) -> URI &;

  /// Get the fragment part of the URI, if any. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/uri.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::URI uri{"https://www.sourcemeta.com/#foo"};
  /// assert(uri.fragment().has_value());
  /// assert(uri.fragment().value() == "foo");
  /// ```
  [[nodiscard]] auto fragment() const -> std::optional<std::string_view>;

  /// Get the non-dissected query part of the URI, if any. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/uri.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::URI
  ///   uri{"https://www.sourcemeta.com/?foo=bar"};
  /// assert(uri.query().has_value());
  /// assert(uri.query().value() == "foo=bar");
  /// ```
  [[nodiscard]] auto query() const -> std::optional<std::string_view>;

  /// Recompose a URI as established by RFC 3986. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/uri.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::URI
  ///   uri{"https://www.sourcemeta.com/foo/../bar"};
  /// assert(uri.recompose() == "https://sourcemeta.com/bar");
  /// ```
  [[nodiscard]] auto recompose() const -> std::string;

  /// Recompose a URI as established by RFC 3986, but without including the
  /// fragment component. The result is an optional to handle the case where the
  /// input URI only consists of a fragment. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/uri.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::URI
  ///   uri{"https://www.sourcemeta.com/foo#bar"};
  /// assert(uri.recompose_without_fragment().has_value()");
  /// assert(uri.recompose_without_fragment().value() ==
  /// "https://sourcemeta.com/foo");
  /// ```
  [[nodiscard]] auto recompose_without_fragment() const
      -> std::optional<std::string>;

  /// Recompose and canonicalize a URI. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/uri.h>
  /// #include <cassert>
  ///
  /// sourcemeta::jsontoolkit::URI uri{"hTtP://exAmpLe.com:80/TEST"};
  /// uri.canonicalize():
  /// assert(uri.recompose() == "http://example.com/TEST");
  /// ```
  auto canonicalize() -> URI &;

  /// Resolve a relative URI against a base URI as established by RFC 3986. For
  /// example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/uri.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::URI base{"https://www.sourcemeta.com"};
  /// sourcemeta::jsontoolkit::URI result{"foo"};
  /// result.resolve_from(base);
  /// assert(result.recompose() == "https://sourcemeta.com/foo");
  /// ```
  auto resolve_from(const URI &base) -> URI &;

  /// Resolve a relative URI against an absolute base URI as established by RFC
  /// 3986. If the base is not a relative URI, nothing happens. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/uri.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::URI base{"bar"};
  /// sourcemeta::jsontoolkit::URI result{"foo"};
  /// result.resolve_from_if_absolute(base);
  /// assert(result.recompose() == "foo");
  /// ```
  auto resolve_from_if_absolute(const URI &base) -> URI &;

  /// Attempt to resolve a URI relative to another URI. If the latter URI is not
  /// a base for the former, leave the URI intact. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/uri.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::URI base{"https://www.sourcemeta.com"};
  /// sourcemeta::jsontoolkit::URI result{"https://www.sourcemeta.com/foo"};
  /// result.relative_to(base);
  /// assert(result.recompose() == "foo");
  /// ```
  auto relative_to(const URI &base) -> URI &;

  /// Escape a string as established by RFC 3986 using C++ standard stream. For
  /// example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/uri.h>
  /// #include <sstream>
  /// #include <cassert>
  ///
  /// std::istringstream input{"foo bar"};
  /// std::ostringstream output;
  /// sourcemeta::jsontoolkit::URI::escape(input, output);
  /// assert(output.str() == "foo%20bar");
  /// ```
  static auto escape(std::istream &input, std::ostream &output) -> void;

  /// Unescape a string that has been percentage-escaped as established by
  /// RFC 3986 using C++ standard streams. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/uri.h>
  /// #include <sstream>
  /// #include <cassert>
  ///
  /// std::istringstream input{"foo%20bar"};
  /// std::ostringstream output;
  /// sourcemeta::jsontoolkit::URI::unescape(input, output);
  /// assert(output.str() == "foo bar");
  /// ```
  static auto unescape(std::istream &input, std::ostream &output) -> void;

  /// Create a URI from a fragment. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/uri.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::URI uri{
  ///   sourcemeta::jsontoolkit::URI::from_fragment("foo")};
  /// assert(uri.recompose() == "#foo");
  /// ```
  static auto from_fragment(std::string_view fragment) -> URI;

  /// Get the user information part of the URI, if any. For example:
  ///
  /// ```cpp
  /// #include <sourcemeta/jsontoolkit/uri.h>
  /// #include <cassert>
  ///
  /// const sourcemeta::jsontoolkit::URI uri{"https://user:@host"};
  /// assert(uri.userinfo().has_value());
  /// assert(uri.userinfo().value() == "user:);
  /// ```
  ///
  /// As mentioned in RFC 3986, the format "user:password" is deprecated.
  /// Applications should not render as clear text any data after the first
  /// colon. See https://tools.ietf.org/html/rfc3986#section-3.2.1
  [[nodiscard]] auto userinfo() const -> std::optional<std::string_view>;

private:
  bool parsed = false;
  auto parse() -> void;

// Exporting symbols that depends on the standard C++ library is considered
// safe.
// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4275?view=msvc-170&redirectedfrom=MSDN
#if defined(_MSC_VER)
#pragma warning(disable : 4251)
#endif
  // We need to keep the string as the URI structure just
  // points to fragments of it.
  // We keep this as const as this class is immutable
  std::string data;

  std::optional<std::string> path_;
  std::optional<std::string> userinfo_;
  std::optional<std::string> host_;
  std::optional<std::uint32_t> port_;
  std::optional<std::string> scheme_;
  std::optional<std::string> fragment_;
  std::optional<std::string> query_;
  bool is_ipv6_ = false;

  // Use PIMPL idiom to hide `urlparser`
  struct Internal;
  std::unique_ptr<Internal> internal;
#if defined(_MSC_VER)
#pragma warning(default : 4251)
#endif
};

} // namespace sourcemeta::jsontoolkit

#endif
