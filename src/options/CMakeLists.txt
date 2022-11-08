add_library(sourcemeta_jsonbinpack_options INTERFACE
  include/jsonbinpack/options/enum.h
  include/jsonbinpack/options/number.h
  include/jsonbinpack/options/string.h)
add_library(sourcemeta::jsonbinpack::options ALIAS sourcemeta_jsonbinpack_options)
target_link_libraries(sourcemeta_jsonbinpack_options INTERFACE
  sourcemeta::jsontoolkit)
target_include_directories(sourcemeta_jsonbinpack_options INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
