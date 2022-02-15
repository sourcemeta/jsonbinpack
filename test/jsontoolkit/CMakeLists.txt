add_executable(sourcemeta_jsontoolkit_unit
  "${PROJECT_SOURCE_DIR}/vendor/googletest/googletest/src/gtest_main.cc"
  json_test.cc utils_test.cc)
add_executable(sourcemeta::jsontoolkit_unit ALIAS sourcemeta_jsontoolkit_unit)
target_link_libraries(sourcemeta_jsontoolkit_unit PRIVATE gtest)
target_link_libraries(sourcemeta_jsontoolkit_unit PRIVATE sourcemeta::jsontoolkit)
gtest_discover_tests(sourcemeta_jsontoolkit_unit)
