add_library(sourcemeta_jsonbinpack_decoder INTERFACE
  include/jsonbinpack/decoder/utils/varint_decoder.h
  include/jsonbinpack/decoder/utils/zigzag_decoder.h
  include/jsonbinpack/decoder/integer_decoder.h
  include/jsonbinpack/decoder/number_decoder.h)
add_library(sourcemeta::jsonbinpack::decoder ALIAS sourcemeta_jsonbinpack_decoder)
target_include_directories(sourcemeta_jsonbinpack_decoder INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(sourcemeta_jsonbinpack_decoder INTERFACE sourcemeta::jsontoolkit)
target_link_libraries(sourcemeta_jsonbinpack_decoder INTERFACE sourcemeta::jsonbinpack::options)
