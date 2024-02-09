noa_library(NAMESPACE sourcemeta PROJECT jsonbinpack NAME encoding
  FOLDER "JSON BinPack/Encoding"
  PRIVATE_HEADERS tag.h wrap.h)

if(JSONBINPACK_INSTALL)
  noa_library_install(NAMESPACE sourcemeta PROJECT jsonbinpack NAME encoding)
endif()

sourcemeta_jsonbinpack_add_compile_options(INTERFACE sourcemeta_jsonbinpack_encoding)

target_link_libraries(sourcemeta_jsonbinpack_encoding INTERFACE
  sourcemeta::jsontoolkit::json)
target_link_libraries(sourcemeta_jsonbinpack_encoding INTERFACE
  sourcemeta::jsonbinpack::numeric)
