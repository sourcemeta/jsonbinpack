add_library(sourcemeta_jsonbinpack_encoding
  include/jsonbinpack/encoding/encoding.h
  include/jsonbinpack/encoding/wrap.h
  encoding.cc)
target_link_libraries(sourcemeta_jsonbinpack_encoding PUBLIC
  sourcemeta_jsontoolkit_json)
target_include_directories(sourcemeta_jsonbinpack_encoding PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
