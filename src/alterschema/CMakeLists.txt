add_library(sourcemeta_alterschema INTERFACE
  include/alterschema/applicator.h
  include/alterschema/bundle.h
  include/alterschema/rule.h)
add_library(sourcemeta::alterschema ALIAS sourcemeta_alterschema)
target_include_directories(sourcemeta_alterschema INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(sourcemeta_alterschema INTERFACE sourcemeta::jsontoolkit)
