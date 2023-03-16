add_library(sourcemeta_alterschema
  include/alterschema/bundle.h
  include/alterschema/rule.h
  bundle.cc rule.cc)
target_include_directories(sourcemeta_alterschema PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(sourcemeta_alterschema PUBLIC sourcemeta_jsontoolkit_json)
target_link_libraries(sourcemeta_alterschema PUBLIC sourcemeta_jsontoolkit_jsonschema)
