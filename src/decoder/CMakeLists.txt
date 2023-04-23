# add_library(sourcemeta_jsonbinpack_decoder INTERFACE
  # include/jsonbinpack/decoder/enum_decoder.h
  # include/jsonbinpack/decoder/integer_decoder.h
  # include/jsonbinpack/decoder/number_decoder.h
  # include/jsonbinpack/decoder/string_decoder.h)
add_library(sourcemeta_jsonbinpack_decoder INTERFACE
  include/jsonbinpack/decoder/varint.h
  include/jsonbinpack/decoder/zigzag.h
  include/jsonbinpack/decoder/basic_decoder.h
  include/jsonbinpack/decoder/decoder.h)
target_include_directories(sourcemeta_jsonbinpack_decoder INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(sourcemeta_jsonbinpack_decoder INTERFACE sourcemeta_jsontoolkit_json)
target_link_libraries(sourcemeta_jsonbinpack_decoder INTERFACE sourcemeta_jsonbinpack_numeric)
target_link_libraries(sourcemeta_jsonbinpack_decoder INTERFACE sourcemeta_jsonbinpack_options)
