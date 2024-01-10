noa_library(NAMESPACE sourcemeta PROJECT jsonbinpack NAME encoder
  FOLDER "JSON BinPack/Encoder"
  PRIVATE_HEADERS varint.h zigzag.h real.h basic.h context.h)

if(JSONBINPACK_INSTALL)
  noa_library_install(NAMESPACE sourcemeta PROJECT jsonbinpack NAME encoder)
endif()

sourcemeta_jsonbinpack_add_compile_options(INTERFACE sourcemeta_jsonbinpack_encoder)

target_link_libraries(sourcemeta_jsonbinpack_encoder INTERFACE
  sourcemeta::jsontoolkit::json)
target_link_libraries(sourcemeta_jsonbinpack_encoder INTERFACE
  sourcemeta::jsonbinpack::numeric)
target_link_libraries(sourcemeta_jsonbinpack_encoder INTERFACE
  sourcemeta::jsonbinpack::encoding)
