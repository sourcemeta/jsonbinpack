configure_file(version.h.in version.h @ONLY)
add_executable(jsonbinpack-cli main.cc)
# To find the generated version file
target_include_directories(jsonbinpack-cli PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
