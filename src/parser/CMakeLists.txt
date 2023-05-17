add_library(sourcemeta_jsonbinpack_parser
  include/jsonbinpack/parser/parser.h parser.cc
  v1_enum.h v1_integer.h v1_number.h v1_string.h)
target_include_directories(sourcemeta_jsonbinpack_parser PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(sourcemeta_jsonbinpack_parser PUBLIC sourcemeta_jsontoolkit_json)
target_link_libraries(sourcemeta_jsonbinpack_parser PRIVATE sourcemeta_jsonbinpack_encoding)
