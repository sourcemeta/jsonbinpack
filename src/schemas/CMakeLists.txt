noa_library(NAMESPACE sourcemeta PROJECT jsonbinpack NAME schemas
  FOLDER "JSON BinPack/Schemas")

if(JSONBINPACK_INSTALL)
  noa_library_install(NAMESPACE sourcemeta PROJECT jsonbinpack NAME schemas)
endif()

sourcemeta_jsonbinpack_add_compile_options(
  INTERFACE sourcemeta_jsonbinpack_schemas)

target_link_libraries(sourcemeta_jsonbinpack_schemas INTERFACE
  sourcemeta::jsontoolkit::json)
