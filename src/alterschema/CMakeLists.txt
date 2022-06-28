add_library(sourcemeta_alterschema INTERFACE)
add_library(sourcemeta::alterschema ALIAS sourcemeta_alterschema)
target_include_directories(sourcemeta_alterschema INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(sourcemeta_alterschema INTERFACE sourcemeta::jsontoolkit)
