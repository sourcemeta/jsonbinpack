add_library(sourcemeta_jsonbinpack_encoder
  include/jsonbinpack/encoder/varint.h
  include/jsonbinpack/encoder/zigzag.h
  include/jsonbinpack/encoder/real.h
  include/jsonbinpack/encoder/basic_encoder.h
  include/jsonbinpack/encoder/encoder.h
  include/jsonbinpack/encoder/context.h context.cc)
target_include_directories(sourcemeta_jsonbinpack_encoder PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(sourcemeta_jsonbinpack_encoder PUBLIC sourcemeta_jsontoolkit_json)
target_link_libraries(sourcemeta_jsonbinpack_encoder PUBLIC sourcemeta_jsonbinpack_options)
