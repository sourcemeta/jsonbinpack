configure_file(version.h.in version.h @ONLY)
add_executable(sourcemeta_jsonbinpack_cli main.cc
  command_help.cc command_version.cc
  command_canonicalize.cc command_compile.cc)
add_executable(sourcemeta::jsonbinpack_cli ALIAS sourcemeta_jsonbinpack_cli)
target_link_libraries(sourcemeta_jsonbinpack_cli PRIVATE sourcemeta::jsonbinpack::canonicalizer)
target_link_libraries(sourcemeta_jsonbinpack_cli PRIVATE sourcemeta::jsonbinpack::mapper)
target_link_libraries(sourcemeta_jsonbinpack_cli PRIVATE sourcemeta::jsontoolkit)

# To find the generated version file
target_include_directories(sourcemeta_jsonbinpack_cli PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
# Set a friendly name for the binary
set_target_properties(sourcemeta_jsonbinpack_cli PROPERTIES
  OUTPUT_NAME jsonbinpack
)
