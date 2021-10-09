add_executable(jsonbinpack_test_stream ../runner.cc magic_test.cc)
add_test(stream jsonbinpack_test_stream COMMAND jsonbinpack_test_stream)
target_link_libraries(jsonbinpack_test_stream gtest)
target_link_libraries(jsonbinpack_test_stream jsonbinpack_stream)

# TODO: It is considered a bad practice to include directories outside of the current directory!!
target_include_directories(jsonbinpack_test_stream PRIVATE "${PROJECT_SOURCE_DIR}")
