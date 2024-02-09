noa_library(NAMESPACE sourcemeta PROJECT jsonbinpack NAME runtime
  FOLDER "JSON BinPack/Runtime"
  PRIVATE_HEADERS
    decoder.h decoder_basic.h
    encoder.h encoder_basic.h encoder_context.h encoder_real.h
    encoding.h encoding_wrap.h
    zigzag.h varint.h numeric.h)

if(JSONBINPACK_INSTALL)
  noa_library_install(NAMESPACE sourcemeta PROJECT jsonbinpack NAME runtime)
endif()

sourcemeta_jsonbinpack_add_compile_options(INTERFACE sourcemeta_jsonbinpack_runtime)

target_link_libraries(sourcemeta_jsonbinpack_runtime INTERFACE
  sourcemeta::jsontoolkit::json)
