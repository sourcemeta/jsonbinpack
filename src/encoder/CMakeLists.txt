add_library(sourcemeta_jsonbinpack_encoder INTERFACE
  include/jsonbinpack/encoder/varint.h
  include/jsonbinpack/encoder/zigzag.h
  include/jsonbinpack/encoder/real.h
  include/jsonbinpack/encoder/basic_encoder.h
  include/jsonbinpack/encoder/encoder.h
  include/jsonbinpack/encoder/context.h)
target_include_directories(sourcemeta_jsonbinpack_encoder INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(sourcemeta_jsonbinpack_encoder INTERFACE sourcemeta::jsontoolkit::json)
target_link_libraries(sourcemeta_jsonbinpack_encoder INTERFACE sourcemeta_jsonbinpack_numeric)
target_link_libraries(sourcemeta_jsonbinpack_encoder INTERFACE sourcemeta_jsonbinpack_encoding)
set_target_properties(sourcemeta_jsonbinpack_encoder
  PROPERTIES FOLDER "JSON BinPack/Encoder")
