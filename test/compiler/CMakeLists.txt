sourcemeta_googletest(NAMESPACE sourcemeta PROJECT jsonbinpack NAME compiler
  FOLDER "JSON BinPack/Compiler"
  SOURCES
    canonicalizer_test.cc compiler_test.cc

    2020_12_compiler_any_test.cc
    2020_12_compiler_integer_test.cc
    2020_12_compiler_number_test.cc)

target_link_libraries(sourcemeta_jsonbinpack_compiler_unit
  PRIVATE sourcemeta::jsonbinpack::compiler)
target_link_libraries(sourcemeta_jsonbinpack_compiler_unit
  PRIVATE sourcemeta::core::json)
target_link_libraries(sourcemeta_jsonbinpack_compiler_unit
  PRIVATE sourcemeta::core::jsonschema)
