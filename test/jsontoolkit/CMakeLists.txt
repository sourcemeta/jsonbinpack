add_executable(jsontoolkit_unit ../runner.cc json_test.cc)
add_test(NAME jsontoolkit_unit COMMAND jsontoolkit_unit)
target_link_libraries(jsontoolkit_unit PRIVATE gtest)
target_link_libraries(jsontoolkit_unit PRIVATE jsontoolkit)
