#ifndef SOURCEMETA_JSONBINPACK_PARSER_V1_ENUM_H_
#define SOURCEMETA_JSONBINPACK_PARSER_V1_ENUM_H_

#include <sourcemeta/jsonbinpack/encoding.h>
#include <sourcemeta/jsontoolkit/json.h>

#include <cassert> // assert
#include <utility> // std::move
#include <vector>  // std::vector

namespace sourcemeta::jsonbinpack::parser::v1 {

auto BYTE_CHOICE_INDEX(const sourcemeta::jsontoolkit::JSON &options)
    -> Encoding {
  assert(options.defines("choices"));
  const auto &choices{options.at("choices")};
  assert(choices.is_array());
  const auto &array{choices.as_array()};
  std::vector<sourcemeta::jsontoolkit::JSON> elements{array.cbegin(),
                                                      array.cend()};
  return sourcemeta::jsonbinpack::BYTE_CHOICE_INDEX({std::move(elements)});
}

auto LARGE_CHOICE_INDEX(const sourcemeta::jsontoolkit::JSON &options)
    -> Encoding {
  assert(options.defines("choices"));
  const auto &choices{options.at("choices")};
  assert(choices.is_array());
  const auto &array{choices.as_array()};
  std::vector<sourcemeta::jsontoolkit::JSON> elements{array.cbegin(),
                                                      array.cend()};
  return sourcemeta::jsonbinpack::LARGE_CHOICE_INDEX({std::move(elements)});
}

auto TOP_LEVEL_BYTE_CHOICE_INDEX(const sourcemeta::jsontoolkit::JSON &options)
    -> Encoding {
  assert(options.defines("choices"));
  const auto &choices{options.at("choices")};
  assert(choices.is_array());
  const auto &array{choices.as_array()};
  std::vector<sourcemeta::jsontoolkit::JSON> elements{array.cbegin(),
                                                      array.cend()};
  return sourcemeta::jsonbinpack::TOP_LEVEL_BYTE_CHOICE_INDEX(
      {std::move(elements)});
}

auto CONST_NONE(const sourcemeta::jsontoolkit::JSON &options) -> Encoding {
  assert(options.defines("value"));
  return sourcemeta::jsonbinpack::CONST_NONE({options.at("value")});
}

} // namespace sourcemeta::jsonbinpack::parser::v1

#endif
