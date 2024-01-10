noa_library(NAMESPACE sourcemeta PROJECT jsonbinpack NAME numeric
  FOLDER "JSON BinPack/Numeric")

if(JSONBINPACK_INSTALL)
  noa_library_install(NAMESPACE sourcemeta PROJECT jsonbinpack NAME numeric)
endif()

sourcemeta_jsonbinpack_add_compile_options(INTERFACE sourcemeta_jsonbinpack_numeric)
