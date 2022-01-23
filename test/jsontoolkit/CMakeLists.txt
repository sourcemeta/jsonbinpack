add_executable(jsontoolkit_unit ../runner.cc json_test.cc)
target_link_libraries(jsontoolkit_unit PRIVATE gtest)
target_link_libraries(jsontoolkit_unit PRIVATE jsontoolkit)
gtest_discover_tests(jsontoolkit_unit)
