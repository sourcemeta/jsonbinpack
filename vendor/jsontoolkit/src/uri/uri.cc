#include <sourcemeta/jsontoolkit/uri.h>
#include <uriparser/Uri.h>

#include <cassert>   // assert
#include <cstdint>   // std::uint32_t
#include <istream>   // std::istream
#include <optional>  // std::optional
#include <sstream>   // std::ostringstream
#include <stdexcept> // std::length_error, std::runtime_error
#include <string>    // std::stoul, std::string, std::tolower
#include <utility>   // std::move
#include <vector>    // std::vector

static auto uri_normalize(UriUriA *uri) -> void {
  if (uriNormalizeSyntaxA(uri) != URI_SUCCESS) {
    throw sourcemeta::jsontoolkit::URIError{"Could not normalize URI"};
  }
}

static auto uri_to_string(const UriUriA *const uri) -> std::string {
  int size;
  if (uriToStringCharsRequiredA(uri, &size) != URI_SUCCESS) {
    throw sourcemeta::jsontoolkit::URIError{"Could not determine URI size"};
  }

  std::string result;
  // Because of this, `uriToStringA` could never error out with
  // `URI_ERROR_OUTPUT_TOO_LARGE`.
  result.resize(static_cast<std::string::size_type>(size));
  if (uriToStringA(result.data(), uri, size + 1, nullptr) != URI_SUCCESS) {
    throw sourcemeta::jsontoolkit::URIError{"Could not stringify URI"};
  }

  return result;
}

static auto uri_text_range(const UriTextRangeA *const range)
    -> std::optional<std::string_view> {
  if (range->afterLast == nullptr) {
    return std::nullopt;
  }

  return std::string_view{range->first,
                          static_cast<std::string_view::size_type>(
                              range->afterLast - range->first)};
}

static auto uri_parse(const std::string &data, UriUriA *uri) -> void {
  const char *error_position;
  switch (uriParseSingleUriA(uri, data.c_str(), &error_position)) {
    case URI_ERROR_SYNTAX:
      // TODO: Test the positions of this error
      throw sourcemeta::jsontoolkit::URIParseError{
          static_cast<std::uint64_t>(error_position - data.c_str() + 1)};
    case URI_ERROR_MALLOC:
      throw std::runtime_error("URI malloc error");
    case URI_ERROR_OUTPUT_TOO_LARGE:
      throw std::length_error("URI output too large");
    case URI_SUCCESS:
      break;
    default:
      throw sourcemeta::jsontoolkit::URIError{"Unknown URI error"};
  }

  uri_normalize(uri);
}

static auto canonicalize_path(const std::string &path, const bool is_relative)
    -> std::optional<std::string> {
  std::vector<std::string> segments;
  std::string segment;

  if (path.empty()) {
    return std::nullopt;
  }

  bool has_leading_with_word = path.front() != '/' && path.front() != '.';
  for (unsigned int i = has_leading_with_word ? 0 : 1; i <= path.size(); i++) {
    char c = path[i];
    if (c == '/' || i == path.size()) {
      if (segment == "..") {
        if (!segments.empty()) {
          segments.pop_back();
        }
      } else if (segment != "." && !segment.empty()) {
        segments.push_back(segment);
      }
      segment.clear();
    } else {
      segment += c;
    }
  }

  // Reconstruct the canonical path
  std::string canonical_path;
  std::string separator = is_relative ? "/" : "";
  for (const auto &seg : segments) {
    canonical_path += separator + seg;
    separator = "/";
  }

  if (canonical_path.empty())
    return std::nullopt;
  return canonical_path;
}

namespace sourcemeta::jsontoolkit {

struct URI::Internal {
  UriUriA uri;
};

URI::URI(std::string input) : data{std::move(input)}, internal{new Internal} {
  this->parse();
}

URI::URI(std::istream &input) : internal{new Internal} {
  std::ostringstream output;
  output << input.rdbuf();
  this->data = output.str();
  this->parse();
}

URI::~URI() { uriFreeUriMembersA(&this->internal->uri); }

// TODO: Test the copy constructor
URI::URI(const URI &other) : URI{other.recompose()} {}

URI::URI(URI &&other)
    : data{std::move(other.data)}, internal{std::move(other.internal)} {
  this->parsed = other.parsed;
  this->path_ = std::move(other.path_);
  this->scheme_ = std::move(other.scheme_);
  this->userinfo_ = std::move(other.userinfo_);
  this->host_ = std::move(other.host_);
  this->port_ = other.port_;
  this->fragment_ = std::move(other.fragment_);
  this->query_ = std::move(other.query_);

  other.internal = nullptr;
}

auto URI::parse() -> void {
  if (this->parsed) {
    // clean
    this->path_ = std::nullopt;
    this->scheme_ = std::nullopt;
    this->userinfo_ = std::nullopt;
    this->host_ = std::nullopt;
    this->port_ = std::nullopt;
    this->fragment_ = std::nullopt;
    this->query_ = std::nullopt;
    this->parsed = false;
    uriFreeUriMembersA(&this->internal->uri);
  }

  // NOTE: we don't skip this line for fast path
  // as the internal structure of uriparser could still
  // be used by resolve_from and relative_to methods
  uri_parse(this->data, &this->internal->uri);

  // Fast path for the root path
  if (this->data == "/") {
    this->path_ = "/";
    this->parsed = true;
    return;
  }

  // Fast path for empty URI
  if (this->data.empty()) {
    this->parsed = true;
    return;
  };

  this->scheme_ = uri_text_range(&this->internal->uri.scheme);
  this->userinfo_ = uri_text_range(&this->internal->uri.userInfo);
  this->host_ = uri_text_range(&this->internal->uri.hostText);
  this->is_ipv6_ = this->internal->uri.hostData.ip6 != nullptr;
  this->fragment_ = uri_text_range(&this->internal->uri.fragment);
  this->query_ = uri_text_range(&this->internal->uri.query);
  const auto port_text{uri_text_range(&this->internal->uri.portText)};
  if (!port_text.has_value()) {
    this->port_ = std::nullopt;
  } else {
    this->port_ = std::stoul(std::string{port_text.value()});
  }

  const UriPathSegmentA *segment{this->internal->uri.pathHead};
  if (segment != nullptr) {
    std::ostringstream path;
    // URNs and tags have a single path segment by definition
    if (this->is_urn() || this->is_tag()) {
      const auto part{uri_text_range(&segment->text)};
      assert(part.has_value());
      path << part.value();
    } else {
      bool first{true};
      while (segment) {
        const auto part{uri_text_range(&segment->text)};
        assert(part.has_value());
        const auto value{part.value()};

        if (first) {
          path << value;
        } else {
          path << "/" << value;
        }

        segment = segment->next;
        first = false;
      }
    }
    this->path_ = path.str();
  }

  this->parsed = true;
}

auto URI::is_relative() const -> bool {
  return !this->scheme().has_value() || this->data.starts_with(".");
}

auto URI::is_absolute() const noexcept -> bool {
  // An absolute URI always contains a scheme component,
  return this->scheme_.has_value();
}

auto URI::is_urn() const -> bool {
  const auto scheme{this->scheme()};
  return scheme.has_value() && scheme.value() == "urn";
}

auto URI::is_tag() const -> bool {
  const auto scheme{this->scheme()};
  return scheme.has_value() && scheme.value() == "tag";
}

auto URI::is_mailto() const -> bool {
  const auto scheme{this->scheme()};
  return scheme.has_value() && scheme.value() == "mailto";
}

auto URI::is_ipv6() const -> bool { return this->is_ipv6_; }

auto URI::is_fragment_only() const -> bool {
  return !this->scheme().has_value() && !this->host().has_value() &&
         !this->port().has_value() && !this->path().has_value() &&
         this->fragment().has_value() && !this->query().has_value();
}

auto URI::scheme() const -> std::optional<std::string_view> {
  return this->scheme_;
}

auto URI::host() const -> std::optional<std::string_view> {
  return this->host_;
}

auto URI::port() const -> std::optional<std::uint32_t> { return this->port_; }

auto URI::path() const -> std::optional<std::string> {
  // NOTE: This is a workaround for the fact that `uriparser` does not
  // parse /.. as a segment, then we store nothing in the path_ field.
  // By that we can't add the initial slash to the URI.
  if (!this->path_.has_value()) {
    if (this->data == "/..") {
      return "/";
    }
    return std::nullopt;
  }

  if (!this->is_urn() && !this->is_tag() && !this->is_mailto() &&
      this->scheme().has_value()) {
    return "/" + this->path_.value();
  }

  if (this->port().has_value() || this->host().has_value()) {
    return "/" + this->path_.value();
  }

  return path_;
}

auto URI::path(const std::string &path) -> URI & {
  if (path.empty()) {
    this->path_ = std::nullopt;
    return *this;
  }

  const auto is_relative_path = path.starts_with(".");
  if (is_relative_path) {
    throw URIError{"You cannot set a relative path"};
  }

  this->path_ = URI{path}.path_;
  return *this;
}

auto URI::path(std::string &&path) -> URI & {
  if (path.empty()) {
    this->path_ = std::nullopt;
    return *this;
  }

  const auto is_relative_path = path.starts_with(".");
  if (is_relative_path) {
    throw URIError{"You cannot set a relative path"};
  }

  this->path_ = URI{std::move(path)}.path_;
  return *this;
}

auto URI::fragment() const -> std::optional<std::string_view> {
  return this->fragment_;
}

auto URI::query() const -> std::optional<std::string_view> {
  return this->query_;
}

auto URI::recompose() const -> std::string {
  std::ostringstream result;

  const auto uri = this->recompose_without_fragment();
  if (uri.has_value()) {
    result << uri.value();
  }

  // Fragment
  const auto result_fragment{this->fragment()};
  if (result_fragment.has_value()) {
    result << '#' << result_fragment.value();
  }

  return result.str();
}

auto URI::recompose_without_fragment() const -> std::optional<std::string> {
  std::ostringstream result;

  // Scheme
  const auto result_scheme{this->scheme()};
  if (result_scheme.has_value()) {
    result << result_scheme.value();
    if (this->is_urn() || this->is_tag() || this->is_mailto()) {
      result << ":";
    } else {
      result << "://";
    }
  }

  const auto user_info{this->userinfo()};
  if (user_info.has_value()) {
    result << user_info.value() << "@";
  }

  // Host
  const auto result_host{this->host()};
  if (result_host.has_value()) {
    if (this->is_ipv6()) {
      // By default uriparser will parse the IPv6 address without brackets
      // so we need to add them manually, as said in the RFC 2732:
      // "To use a literal IPv6 address in a URL, the literal address should be
      // enclosed in "[" and "]" characters."
      // See https://tools.ietf.org/html/rfc2732#section-2
      result << '[' << result_host.value() << ']';
    } else {
      result << result_host.value();
    }
  }

  // Port
  const auto result_port{this->port()};
  if (result_port.has_value()) {
    result << ':' << result_port.value();
  }

  // Path
  const auto result_path{this->path()};
  if (result_path.has_value()) {
    result << result_path.value();
  }

  // Query
  const auto result_query{this->query()};
  if (result_query.has_value()) {
    result << '?' << result_query.value();
  }

  if (result.tellp() == 0) {
    return std::nullopt;
  }

  return result.str();
}

auto URI::canonicalize() -> URI & {
  // Scheme
  const auto result_scheme{this->scheme()};
  if (result_scheme.has_value()) {
    std::ostringstream lowercased_scheme;
    for (const auto character : result_scheme.value()) {
      lowercased_scheme << static_cast<char>(std::tolower(character));
    }
    this->scheme_ = lowercased_scheme.str();
  }

  // Host
  const auto result_host{this->host()};
  if (result_host.has_value()) {
    std::ostringstream lowercased_host;
    for (const auto character : result_host.value()) {
      lowercased_host << static_cast<char>(std::tolower(character));
    }
    this->host_ = lowercased_host.str();
  }

  // Clean Path form ".." and "."
  const auto result_path{this->path()};
  if (result_path.has_value()) {
    const auto canonical_path{
        canonicalize_path(result_path.value(), this->is_relative())};
    if (canonical_path.has_value()) {
      this->path_ = canonical_path.value();
    }
  }

  // Fragment
  // The empty fragment is optional
  const auto result_fragment{this->fragment()};
  if (result_fragment.has_value() && !result_fragment.value().empty()) {
    this->fragment_ = result_fragment.value();
  } else {
    this->fragment_ = std::nullopt;
  }

  // Port
  const auto result_port{this->port()};
  if (result_port.has_value()) {
    const bool is_default_http_port{result_scheme.has_value() &&
                                    result_scheme.value() == "http" &&
                                    result_port.value() == 80};
    const bool is_default_https_port{result_scheme.has_value() &&
                                     result_scheme.value() == "https" &&
                                     result_port.value() == 443};

    if (!is_default_http_port && !is_default_https_port) {
      this->port_ = result_port.value();
    } else {
      this->port_ = std::nullopt;
    }
  }

  return *this;
}

auto URI::resolve_from(const URI &base) -> URI & {
  UriUriA absoluteDest;
  // Looks like this function allocates to the output variable
  // even on failure.
  // See https://uriparser.github.io/doc/api/latest/
  switch (uriAddBaseUriExA(&absoluteDest, &this->internal->uri,
                           &base.internal->uri, URI_RESOLVE_STRICTLY)) {
    case URI_SUCCESS:
      break;
    case URI_ERROR_ADDBASE_REL_BASE:
      uriFreeUriMembersA(&absoluteDest);
      assert(!base.is_absolute());
      throw URIError{"Base URI is not absolute"};
    default:
      uriFreeUriMembersA(&absoluteDest);
      throw URIError{"Could not resolve URI"};
  }

  try {
    uri_normalize(&absoluteDest);
    this->data = uri_to_string(&absoluteDest);
    uriFreeUriMembersA(&absoluteDest);
    this->parse();
    return *this;
  } catch (...) {
    uriFreeUriMembersA(&absoluteDest);
    throw;
  }
}

auto URI::relative_to(const URI &base) -> URI & {
  if (!this->is_absolute() || !base.is_absolute() ||
      this->host() != base.host()) {
    return *this;
  }

  UriUriA result;
  URI copy{*this};

  // According to the docs, we only need to free on success
  // See
  // https://uriparser.github.io/doc/api/latest/Uri_8h.html#a20cc7888b62700d6cb7e7896647b0d5d
  switch (uriRemoveBaseUriMmA(&result, &copy.internal->uri, &base.internal->uri,
                              URI_FALSE, nullptr)) {
    case URI_SUCCESS:
      break;
    default:
      throw URIError{"Could not resolve URI relative to the given base"};
  }

  try {
    uri_normalize(&result);
    copy.data = uri_to_string(&result);
  } catch (...) {
    uriFreeUriMembersMmA(&result, nullptr);
    throw;
  }

  uriFreeUriMembersMmA(&result, nullptr);
  copy.parse();

  // `uriparser` has this weird thing where it will only look at scheme and
  // authority, incorrectly thinking that a certain URI is a base of another one
  // if the path of the former exceeds the path of the latter. This is an ugly
  // workaround to prevent this non-sense.
  if (!copy.recompose().empty() || base.recompose() == this->recompose()) {
    this->data = std::move(copy.data);
    this->parse();
  }

  return *this;
}

auto URI::from_fragment(std::string_view fragment) -> URI {
  assert(fragment.empty() || fragment.front() != '#');
  std::ostringstream uri;
  uri << "#" << fragment;
  return {uri.str()};
}

auto URI::resolve_from_if_absolute(const URI &base) -> URI & {
  if (base.is_absolute()) {
    return this->resolve_from(base);
  } else {
    return *this;
  }
}

auto URI::userinfo() const -> std::optional<std::string_view> {
  return this->userinfo_;
}

} // namespace sourcemeta::jsontoolkit
