# We leave the door open for implementing the JSON class
# using different backends if needed.
add_library(sourcemeta_jsontoolkit json_rapidjson.cc)
target_compile_definitions(sourcemeta_jsontoolkit PRIVATE SOURCEMETA_JSONTOOLKIT_BACKEND_RAPIDJSON)

add_library(sourcemeta::jsontoolkit ALIAS sourcemeta_jsontoolkit)
target_include_directories(sourcemeta_jsontoolkit PRIVATE "${PROJECT_SOURCE_DIR}/vendor/rapidjson/include")
target_include_directories(sourcemeta_jsontoolkit INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
