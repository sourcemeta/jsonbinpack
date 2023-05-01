add_library(sourcemeta_jsonbinpack_options
  include/jsonbinpack/options/options.h
  include/jsonbinpack/options/wrap.h
  options.cc)
target_link_libraries(sourcemeta_jsonbinpack_options PUBLIC
  sourcemeta_jsontoolkit_json)
target_include_directories(sourcemeta_jsonbinpack_options PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
