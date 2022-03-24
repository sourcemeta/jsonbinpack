# Unit Tests
add_executable(sourcemeta_jsontoolkit_unit
  "${PROJECT_SOURCE_DIR}/vendor/googletest/googletest/src/gtest_main.cc"
  json_test.cc
  array_test.cc string_test.cc object_test.cc
  number_test.cc null_test.cc boolean_test.cc)
add_executable(sourcemeta::jsontoolkit_unit ALIAS sourcemeta_jsontoolkit_unit)
target_link_libraries(sourcemeta_jsontoolkit_unit PRIVATE gtest)
target_link_libraries(sourcemeta_jsontoolkit_unit PRIVATE sourcemeta::jsontoolkit)
gtest_discover_tests(sourcemeta_jsontoolkit_unit)

# JSON Test Suite
add_executable(sourcemeta_jsontoolkit_jsontestsuite jsontestsuite.cc)
add_executable(sourcemeta::jsontoolkit_jsontestsuite ALIAS sourcemeta_jsontoolkit_jsontestsuite)
target_compile_definitions(sourcemeta_jsontoolkit_jsontestsuite
  PRIVATE JSONTESTSUITE_PATH="${PROJECT_SOURCE_DIR}/vendor/jsontestsuite")
target_link_libraries(sourcemeta_jsontoolkit_jsontestsuite PRIVATE gtest)
target_link_libraries(sourcemeta_jsontoolkit_jsontestsuite PRIVATE sourcemeta::jsontoolkit)
gtest_discover_tests(sourcemeta_jsontoolkit_jsontestsuite)
