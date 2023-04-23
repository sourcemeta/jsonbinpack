add_library(sourcemeta_jsonbinpack_options INTERFACE
  include/jsonbinpack/options/enum.h
  include/jsonbinpack/options/integer.h
  include/jsonbinpack/options/string.h)
target_link_libraries(sourcemeta_jsonbinpack_options INTERFACE
  sourcemeta_jsontoolkit_json)
target_include_directories(sourcemeta_jsonbinpack_options INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
