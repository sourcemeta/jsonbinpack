#include "parser.h"
#include <jsontoolkit/json.h>
#include <stdexcept> // std::domain_error
#include <utility>   // std::make_pair

template <typename Wrapper>
auto sourcemeta::jsontoolkit::parser::object(
    const std::string_view &input,
    std::unordered_map<std::string_view, Wrapper> &output) -> void {
  const std::string_view document =
      sourcemeta::jsontoolkit::parser::trim(input);
  if (document.front() != sourcemeta::jsontoolkit::parser::JSON_OBJECT_START ||
      document.back() != sourcemeta::jsontoolkit::parser::JSON_OBJECT_END) {
    throw std::domain_error("Invalid object");
  }

  // TODO: Implement this for real
  output.insert(std::make_pair("foo", Wrapper(document)));
  output.clear();
}

template void
sourcemeta::jsontoolkit::parser::object<sourcemeta::jsontoolkit::JSON>(
    const std::string_view &,
    std::unordered_map<std::string_view, sourcemeta::jsontoolkit::JSON> &);
