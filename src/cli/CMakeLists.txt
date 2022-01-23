configure_file(version.h.in version.h @ONLY)
add_executable(sourcemeta_jsonbinpack_cli main.cc)
add_executable(sourcemeta::jsonbinpack_cli ALIAS sourcemeta_jsonbinpack_cli)
# To find the generated version file
target_include_directories(sourcemeta_jsonbinpack_cli PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
