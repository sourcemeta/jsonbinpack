if(NOT JSONToolkit_FOUND)
  set(JSONTOOLKIT_JSONL OFF CACHE BOOL "disable JSONL support")
  add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/jsontoolkit")
  set(JSONToolkit_FOUND ON)
endif()
