add_executable(jsonbinpack_test runner.cc 
  stream/magic_test.cc
)

target_compile_options(jsonbinpack_test PRIVATE -Wall -Wextra -Werror)

add_test(JSONBINPACK jsonbinpack_test COMMAND jsonbinpack_test)

target_link_libraries(jsonbinpack_test gtest)
target_link_libraries(jsonbinpack_test jsonbinpack_stream)
target_include_directories(jsonbinpack_test PUBLIC "${PROJECT_SOURCE_DIR}")
