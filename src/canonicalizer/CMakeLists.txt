add_library(sourcemeta_jsonbinpack_canonicalizer
  src/rule.cc src/bundle.cc src/canonicalizer.cc)
add_library(sourcemeta::jsonbinpack::canonicalizer ALIAS sourcemeta_jsonbinpack_canonicalizer)
target_include_directories(sourcemeta_jsonbinpack_canonicalizer PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(sourcemeta_jsonbinpack_canonicalizer INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(sourcemeta_jsonbinpack_canonicalizer PRIVATE sourcemeta::jsontoolkit)
