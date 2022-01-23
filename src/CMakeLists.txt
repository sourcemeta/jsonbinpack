add_subdirectory(jsontoolkit)
add_subdirectory(cli)

# Define the final library to install
# TODO: Support creating a shared library instead,
# automatically generating exports with CMake's
# generate_export_header()
add_library(jsonbinpack INTERFACE)
add_library(sourcemeta::jsonbinpack ALIAS jsonbinpack)
target_link_libraries(jsonbinpack INTERFACE jsontoolkit)
