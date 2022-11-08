add_library(sourcemeta_jsonbinpack_encoder INTERFACE
  include/jsonbinpack/encoder/utils/real.h
  include/jsonbinpack/encoder/utils/varint_encoder.h
  include/jsonbinpack/encoder/utils/zigzag_encoder.h
  include/jsonbinpack/encoder/enum_encoder.h
  include/jsonbinpack/encoder/integer_encoder.h
  include/jsonbinpack/encoder/number_encoder.h
  include/jsonbinpack/encoder/string_encoder.h)
add_library(sourcemeta::jsonbinpack::encoder ALIAS sourcemeta_jsonbinpack_encoder)
target_include_directories(sourcemeta_jsonbinpack_encoder INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(sourcemeta_jsonbinpack_encoder INTERFACE sourcemeta::jsontoolkit)
target_link_libraries(sourcemeta_jsonbinpack_encoder INTERFACE sourcemeta::jsonbinpack::options)
