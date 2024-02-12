noa_library(NAMESPACE sourcemeta PROJECT jsonbinpack NAME parser
  FOLDER "JSON BinPack/Parser" SOURCES parser.cc v1.h)

if(JSONBINPACK_INSTALL)
  noa_library_install(NAMESPACE sourcemeta PROJECT jsonbinpack NAME parser)
endif()

sourcemeta_jsonbinpack_add_compile_options(PRIVATE sourcemeta_jsonbinpack_parser)

target_link_libraries(sourcemeta_jsonbinpack_parser PUBLIC
  sourcemeta::jsontoolkit::json)
target_link_libraries(sourcemeta_jsonbinpack_parser PRIVATE
  sourcemeta::jsonbinpack::runtime)
