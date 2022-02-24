#ifndef SOURCEMETA_JSONTOOLKIT_JSON_NUMBER_H_
#define SOURCEMETA_JSONTOOLKIT_JSON_NUMBER_H_

#include <cstdint>     // std::int64_t
#include <string_view> // std::string_view
#include <variant>     // std::variant

namespace sourcemeta::jsontoolkit {
class GenericNumber {
public:
  GenericNumber();
  GenericNumber(const std::string_view &document);
  GenericNumber(std::int64_t value);
  GenericNumber(double value);
  auto integer_value() -> std::int64_t;
  auto real_value() -> double;
  auto is_integer() -> bool;

private:
  const std::string_view source;
  auto parse() -> GenericNumber &;
  bool must_parse;
  std::variant<std::int64_t, double> data;
};
} // namespace sourcemeta::jsontoolkit

#endif
