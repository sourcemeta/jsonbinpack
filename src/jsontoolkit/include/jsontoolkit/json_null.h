#ifndef SOURCEMETA_JSONTOOLKIT_JSON_NULL_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_NULL_H_

#include <cstddef>     // std::nullptr_t
#include <stdexcept>   // std::domain_error
#include <string>      // std::string
#include <string_view> // std::string_view

namespace sourcemeta::jsontoolkit::Null {

constexpr std::string_view token_constant{"null"};
auto parse(std::string_view document) -> std::nullptr_t;
auto stringify() -> std::string;

} // namespace sourcemeta::jsontoolkit::Null

#endif
