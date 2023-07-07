add_library(sourcemeta_jsonbinpack_encoding
  include/jsonbinpack/encoding/encoding.h
  include/jsonbinpack/encoding/wrap.h
  include/jsonbinpack/encoding/tag.h
  encoding.cc)
target_link_libraries(sourcemeta_jsonbinpack_encoding PUBLIC
  sourcemeta::jsontoolkit::json)
target_link_libraries(sourcemeta_jsonbinpack_encoding PUBLIC
  sourcemeta_jsonbinpack_numeric)
target_include_directories(sourcemeta_jsonbinpack_encoding PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
