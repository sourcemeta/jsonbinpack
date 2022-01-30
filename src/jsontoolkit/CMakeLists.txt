if(JSONTOOLKIT_BACKEND STREQUAL "rapidjson")
  set(sourcemeta_jsontoolkit_files "src/backends/${JSONTOOLKIT_BACKEND}.cc")
  set(sourcemeta_jsontoolkit_includes_private "${PROJECT_SOURCE_DIR}/vendor/rapidjson/include")
  set(sourcemeta_jsontoolkit_includes_interface "${PROJECT_SOURCE_DIR}/vendor/rapidjson/include")
else()
  message(FATAL_ERROR "Unknown backend: ${JSONTOOLKIT_BACKEND}")
endif()

add_library(sourcemeta_jsontoolkit ${sourcemeta_jsontoolkit_files})
target_compile_definitions(sourcemeta_jsontoolkit PRIVATE
  SOURCEMETA_JSONTOOLKIT_BACKEND=${JSONTOOLKIT_BACKEND})
add_library(sourcemeta::jsontoolkit ALIAS sourcemeta_jsontoolkit)

target_include_directories(sourcemeta_jsontoolkit PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/include" ${sourcemeta_jsontoolkit_includes_private})
target_include_directories(sourcemeta_jsontoolkit INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include" ${sourcemeta_jsontoolkit_includes_interface})
