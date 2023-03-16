include(GoogleTest)
find_package(GTest)

if(NOT GTest_FOUND)
  # See https://packages.ubuntu.com/kinetic/all/googletest/filelist
  if(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND EXISTS /usr/src/googletest/CMakeLists.txt)
    add_subdirectory(/usr/src/googletest "${CMAKE_CURRENT_BINARY_DIR}/vendor/googletest")
  else()
    message(FATAL_ERROR "Could NOT find GTest")
  endif()
endif()

# Some GNU/Linux distros lack the namespace
if(NOT TARGET GTest::gtest)
  add_library(GTest::gtest ALIAS gtest)
endif()
if(NOT TARGET GTest::gtest_main)
  add_library(GTest::gtest_main ALIAS gtest_main)
endif()
