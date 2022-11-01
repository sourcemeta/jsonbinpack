add_executable(sourcemeta_alterschema_unit
  "${PROJECT_SOURCE_DIR}/vendor/googletest/googletest/src/gtest_main.cc"
  bundle_test.cc rule_test.cc sample_rules.h)
add_executable(sourcemeta::alterschema_unit ALIAS sourcemeta_alterschema_unit)
target_link_libraries(sourcemeta_alterschema_unit PRIVATE gtest)
target_link_libraries(sourcemeta_alterschema_unit PRIVATE sourcemeta::alterschema)
gtest_discover_tests(sourcemeta_alterschema_unit)
