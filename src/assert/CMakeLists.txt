add_library(sourcemeta_assert INTERFACE)
add_library(sourcemeta::assert ALIAS sourcemeta_assert)
target_include_directories(sourcemeta_assert INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
