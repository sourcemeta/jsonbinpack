add_library(sourcemeta_jsonbinpack_options INTERFACE
  include/jsonbinpack/options/number.h)
add_library(sourcemeta::jsonbinpack::options ALIAS sourcemeta_jsonbinpack_options)
target_include_directories(sourcemeta_jsonbinpack_options INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
