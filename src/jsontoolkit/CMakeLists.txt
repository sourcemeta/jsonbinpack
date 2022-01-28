add_library(sourcemeta_jsontoolkit src/json.cc)
target_compile_definitions(sourcemeta_jsontoolkit PRIVATE RAPIDJSON_HAS_STDSTRING)
add_library(sourcemeta::jsontoolkit ALIAS sourcemeta_jsontoolkit)
target_include_directories(sourcemeta_jsontoolkit PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
  "${PROJECT_SOURCE_DIR}/vendor/rapidjson/include")
target_include_directories(sourcemeta_jsontoolkit INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
  "${PROJECT_SOURCE_DIR}/vendor/rapidjson/include")
