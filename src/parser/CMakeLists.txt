noa_library(NAMESPACE sourcemeta PROJECT jsonbinpack NAME parser
  FOLDER "JSON BinPack/Parser"
  SOURCES parser.cc v1_any.h v1_array.h v1_enum.h v1_integer.h v1_number.h v1_string.h)

if(JSONBINPACK_INSTALL)
  noa_library_install(NAMESPACE sourcemeta PROJECT jsonbinpack NAME parser)
endif()

sourcemeta_jsonbinpack_add_compile_options(PRIVATE sourcemeta_jsonbinpack_parser)

target_link_libraries(sourcemeta_jsonbinpack_parser PUBLIC
  sourcemeta::jsontoolkit::json)
target_link_libraries(sourcemeta_jsonbinpack_parser PRIVATE
  sourcemeta::jsonbinpack::encoding)
