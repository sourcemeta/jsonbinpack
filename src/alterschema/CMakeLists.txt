add_library(sourcemeta_alterschema src/rule.cc src/bundle.cc)
add_library(sourcemeta::alterschema ALIAS sourcemeta_alterschema)
target_include_directories(sourcemeta_alterschema PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(sourcemeta_alterschema INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(sourcemeta_alterschema PRIVATE sourcemeta::jsontoolkit)
