add_library(sourcemeta_alterschema
  include/alterschema/bundle.h
  include/alterschema/rule.h
  bundle.cc rule.cc)
target_include_directories(sourcemeta_alterschema PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(sourcemeta_alterschema PUBLIC sourcemeta::jsontoolkit::json)
target_link_libraries(sourcemeta_alterschema PUBLIC sourcemeta::jsontoolkit::jsonschema)
set_target_properties(sourcemeta_alterschema
  PROPERTIES FOLDER "JSON BinPack/Alterschema")
