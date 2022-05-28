add_executable(sourcemeta_assert_unit
  "${PROJECT_SOURCE_DIR}/vendor/googletest/googletest/src/gtest_main.cc"
  check_test.cc)
add_executable(sourcemeta::assert_unit ALIAS sourcemeta_assert_unit)
target_link_libraries(sourcemeta_assert_unit PRIVATE gtest)
target_link_libraries(sourcemeta_assert_unit PRIVATE sourcemeta::assert)
gtest_discover_tests(sourcemeta_assert_unit)
