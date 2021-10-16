configure_file(config.h.in config.h)
add_executable(jsonbinpack main.cc command_version.cc command_help.cc)
target_include_directories(jsonbinpack PRIVATE
  "${CMAKE_CURRENT_BINARY_DIR}" # so that we can consume config.h
  "${PROJECT_SOURCE_DIR}")
