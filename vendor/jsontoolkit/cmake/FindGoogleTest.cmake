set(BUILD_GMOCK OFF CACHE BOOL "disable googlemock")
set(INSTALL_GTEST OFF CACHE BOOL "disable installation")
add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/googletest")
set(GoogleTest_FOUND ON)
