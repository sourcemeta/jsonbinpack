add_executable(jsontoolkit_unit ../runner.cc json_test.cc)
target_link_libraries(jsontoolkit_unit PRIVATE gtest)
target_link_libraries(jsontoolkit_unit PRIVATE jsontoolkit)
gtest_add_tests(TARGET jsontoolkit_unit)
