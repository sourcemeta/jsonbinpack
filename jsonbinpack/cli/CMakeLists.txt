configure_file(config.h.in config.h)
add_executable(jsonbinpack main.cc)
target_link_libraries(jsonbinpack PRIVATE jsonbinpack_stream)
target_include_directories(jsonbinpack PRIVATE
  "${CMAKE_CURRENT_BINARY_DIR}" # so that we can consume config.h
  "${PROJECT_SOURCE_DIR}")
