if(NOT JSONToolkit_FOUND)
  add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/jsontoolkit")
  set(JSONToolkit_FOUND ON)
endif()
