#ifndef SOURCEMETA_JSONTOOLKIT_JSON_NUMBER_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_NUMBER_H_

#include <cstdint>     // std::int64_t
#include <string_view> // std::string_view
#include <variant>     // std::variant

namespace sourcemeta::jsontoolkit {

auto parse_number(const std::string_view &input)
    -> std::variant<std::int64_t, double>;

} // namespace sourcemeta::jsontoolkit

#endif
