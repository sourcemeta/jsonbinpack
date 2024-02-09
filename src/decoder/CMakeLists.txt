noa_library(NAMESPACE sourcemeta PROJECT jsonbinpack NAME decoder
  FOLDER "JSON BinPack/Decoder"
  PRIVATE_HEADERS varint.h zigzag.h basic.h)

if(JSONBINPACK_INSTALL)
  noa_library_install(NAMESPACE sourcemeta PROJECT jsonbinpack NAME decoder)
endif()

sourcemeta_jsonbinpack_add_compile_options(INTERFACE sourcemeta_jsonbinpack_decoder)

target_link_libraries(sourcemeta_jsonbinpack_decoder INTERFACE
  sourcemeta::jsontoolkit::json)
target_link_libraries(sourcemeta_jsonbinpack_decoder INTERFACE
  sourcemeta::jsonbinpack::numeric)
target_link_libraries(sourcemeta_jsonbinpack_decoder INTERFACE
  sourcemeta::jsonbinpack::encoding)
