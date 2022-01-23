add_subdirectory(jsontoolkit)
add_subdirectory(cli)

# Define the final library to install
# TODO: Support creating a shared library instead,
# automatically generating exports with CMake's
# generate_export_header()
add_library(sourcemeta_jsonbinpack INTERFACE)
add_library(sourcemeta::jsonbinpack ALIAS sourcemeta_jsonbinpack)
target_link_libraries(sourcemeta_jsonbinpack INTERFACE sourcemeta_jsontoolkit)
