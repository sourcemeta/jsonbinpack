#ifndef SOURCEMETA_JSONBINPACK_OPTIONS_ENUM_H_
#define SOURCEMETA_JSONBINPACK_OPTIONS_ENUM_H_

#include <vector> // std::vector

namespace sourcemeta::jsonbinpack::options {

template <typename Source> struct EnumOptions {
  std::vector<sourcemeta::jsontoolkit::JSON<Source>> choices;
};

template <typename Source> struct StaticOptions {
  sourcemeta::jsontoolkit::JSON<Source> value;
};

} // namespace sourcemeta::jsonbinpack::options

#endif
