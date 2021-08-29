configure_file(config.h.in config.h)
add_executable(jsonbinpack main.cc)
target_compile_options(jsonbinpack PRIVATE -Wall -Wextra -Werror)
target_link_libraries(jsonbinpack PUBLIC jsonbinpack_stream)
target_include_directories(jsonbinpack PUBLIC 
  "${CMAKE_CURRENT_BINARY_DIR}" # so that we can consume config.h
  "${PROJECT_SOURCE_DIR}")
