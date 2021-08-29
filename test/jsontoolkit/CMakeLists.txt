add_executable(jsontoolkit_test ../runner.cc json_test.cc)
add_test(jsontoolkit jsontoolkit_test COMMAND jsontoolkit_test)
target_link_libraries(jsontoolkit_test gtest)
target_link_libraries(jsontoolkit_test jsontoolkit)
