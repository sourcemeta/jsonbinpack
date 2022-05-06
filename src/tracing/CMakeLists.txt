add_library(sourcemeta_tracing INTERFACE)
add_library(sourcemeta::tracing ALIAS sourcemeta_tracing)
target_include_directories(sourcemeta_tracing INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
