#ifndef SOURCEMETA_JSONBINPACK_RUNTIME_LOADER_V1_ARRAY_H_
#define SOURCEMETA_JSONBINPACK_RUNTIME_LOADER_V1_ARRAY_H_

#include <sourcemeta/jsonbinpack/runtime.h>
#include <sourcemeta/jsonbinpack/runtime_encoding_wrap.h>

#include <sourcemeta/jsontoolkit/json.h>

#include <algorithm> // std::transform
#include <cassert>   // assert
#include <cstdint>   // std::uint64_t
#include <iterator>  // std::back_inserter
#include <vector>    // std::vector

namespace sourcemeta::jsonbinpack::v1 {

auto FIXED_TYPED_ARRAY(const sourcemeta::jsontoolkit::JSON &options)
    -> Encoding {
  assert(options.defines("size"));
  assert(options.defines("encoding"));
  assert(options.defines("prefixEncodings"));
  const auto &size{options.at("size")};
  const auto &array_encoding{options.at("encoding")};
  const auto &prefix_encodings{options.at("prefixEncodings")};
  assert(size.is_integer());
  assert(size.is_positive());
  assert(array_encoding.is_object());
  assert(prefix_encodings.is_array());
  std::vector<Encoding> encodings;
  std::transform(prefix_encodings.as_array().cbegin(),
                 prefix_encodings.as_array().cend(),
                 std::back_inserter(encodings),
                 [](const auto &element) { return load(element); });
  assert(encodings.size() == prefix_encodings.size());
  return sourcemeta::jsonbinpack::FIXED_TYPED_ARRAY{
      static_cast<std::uint64_t>(size.to_integer()), wrap(load(array_encoding)),
      wrap(encodings.begin(), encodings.end())};
}

auto BOUNDED_8BITS_TYPED_ARRAY(const sourcemeta::jsontoolkit::JSON &options)
    -> Encoding {
  assert(options.defines("minimum"));
  assert(options.defines("maximum"));
  assert(options.defines("encoding"));
  assert(options.defines("prefixEncodings"));
  const auto &minimum{options.at("minimum")};
  const auto &maximum{options.at("maximum")};
  const auto &array_encoding{options.at("encoding")};
  const auto &prefix_encodings{options.at("prefixEncodings")};
  assert(minimum.is_integer());
  assert(maximum.is_integer());
  assert(minimum.is_positive());
  assert(maximum.is_positive());
  assert(array_encoding.is_object());
  assert(prefix_encodings.is_array());
  std::vector<Encoding> encodings;
  std::transform(prefix_encodings.as_array().cbegin(),
                 prefix_encodings.as_array().cend(),
                 std::back_inserter(encodings),
                 [](const auto &element) { return load(element); });
  assert(encodings.size() == prefix_encodings.size());
  return sourcemeta::jsonbinpack::BOUNDED_8BITS_TYPED_ARRAY{
      static_cast<std::uint64_t>(minimum.to_integer()),
      static_cast<std::uint64_t>(maximum.to_integer()),
      wrap(load(array_encoding)), wrap(encodings.begin(), encodings.end())};
}

auto FLOOR_TYPED_ARRAY(const sourcemeta::jsontoolkit::JSON &options)
    -> Encoding {
  assert(options.defines("minimum"));
  assert(options.defines("encoding"));
  assert(options.defines("prefixEncodings"));
  const auto &minimum{options.at("minimum")};
  const auto &array_encoding{options.at("encoding")};
  const auto &prefix_encodings{options.at("prefixEncodings")};
  assert(minimum.is_integer());
  assert(minimum.is_positive());
  assert(array_encoding.is_object());
  assert(prefix_encodings.is_array());
  std::vector<Encoding> encodings;
  std::transform(prefix_encodings.as_array().cbegin(),
                 prefix_encodings.as_array().cend(),
                 std::back_inserter(encodings),
                 [](const auto &element) { return load(element); });
  assert(encodings.size() == prefix_encodings.size());
  return sourcemeta::jsonbinpack::FLOOR_TYPED_ARRAY{
      static_cast<std::uint64_t>(minimum.to_integer()),
      wrap(load(array_encoding)), wrap(encodings.begin(), encodings.end())};
}

auto ROOF_TYPED_ARRAY(const sourcemeta::jsontoolkit::JSON &options)
    -> Encoding {
  assert(options.defines("maximum"));
  assert(options.defines("encoding"));
  assert(options.defines("prefixEncodings"));
  const auto &maximum{options.at("maximum")};
  const auto &array_encoding{options.at("encoding")};
  const auto &prefix_encodings{options.at("prefixEncodings")};
  assert(maximum.is_integer());
  assert(maximum.is_positive());
  assert(array_encoding.is_object());
  assert(prefix_encodings.is_array());
  std::vector<Encoding> encodings;
  std::transform(prefix_encodings.as_array().cbegin(),
                 prefix_encodings.as_array().cend(),
                 std::back_inserter(encodings),
                 [](const auto &element) { return load(element); });
  assert(encodings.size() == prefix_encodings.size());
  return sourcemeta::jsonbinpack::ROOF_TYPED_ARRAY{
      static_cast<std::uint64_t>(maximum.to_integer()),
      wrap(load(array_encoding)), wrap(encodings.begin(), encodings.end())};
}

} // namespace sourcemeta::jsonbinpack::v1

#endif
