add_library(jsontoolkit json.cc)
target_link_libraries(jsontoolkit PRIVATE rapidjson)
target_include_directories(jsontoolkit INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
# target_include_directories(jsontoolkit PRIVATE "${PROJECT_SOURCE_DIR}/vendor/rapidjson/include")
