# Standards (sane modern defaults)
if("CXX" IN_LIST NOA_LANGUAGES)
  set(CMAKE_CXX_STANDARD 20)
endif()
if("C" IN_LIST NOA_LANGUAGES)
  set(CMAKE_C_STANDARD 11)
endif()
if("OBJCXX" IN_LIST NOA_LANGUAGES)
  set(CMAKE_OBJCXX_STANDARD "${CMAKE_CXX_STANDARD}")
endif()

# Hide symbols from shared libraries by default
# In certain compilers, like GCC and Clang,
# symbols are visible by default.
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)
if("CXX" IN_LIST NOA_LANGUAGES)
  set(CMAKE_CXX_VISIBILITY_PRESET hidden)
endif()
if("C" IN_LIST NOA_LANGUAGES)
  set(CMAKE_C_VISIBILITY_PRESET hidden)
endif()
if("OBJCXX" IN_LIST NOA_LANGUAGES)
  set(CMAKE_OBJCXX_VISIBILITY_PRESET hidden)
endif()

# By default, stay within ISO C++
if("CXX" IN_LIST NOA_LANGUAGES)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()
if("C" IN_LIST NOA_LANGUAGES)
  set(CMAKE_C_STANDARD_REQUIRED ON)
  set(CMAKE_C_EXTENSIONS OFF)
endif()
if("OBJCXX" IN_LIST NOA_LANGUAGES)
  set(CMAKE_OBJCXX_STANDARD_REQUIRED ON)
  set(CMAKE_OBJCXX_EXTENSIONS OFF)
endif()

# Export compile commands by default.
# It is very useful for IDE integration, linting, etc
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Prevent DT_RPATH/DT_RUNPATH problem
# This problem is not present on Apple platforms.
# See https://www.youtube.com/watch?v=m0DwB4OvDXk
if(NOT APPLE)
  set(CMAKE_INSTALL_RPATH $ORIGIN)
endif()

# Delay GoogleTest discovery until before running the tests
# See https://discourse.cmake.org/t/default-value-for-new-discovery-mode-option-for-gtest-discover-tests/1422
set(CMAKE_GTEST_DISCOVER_TESTS_DISCOVERY_MODE PRE_TEST)

# Always use folders in IDE
# See https://cmake.org/cmake/help/latest/prop_gbl/USE_FOLDERS.html
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
