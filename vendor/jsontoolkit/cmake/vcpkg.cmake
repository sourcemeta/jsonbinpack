# Attempt to find vcpkg from standard locations
find_file(VCPKG_CMAKE_TOOLCHAIN
  NAMES scripts/buildsystems/vcpkg.cmake
  PATHS C:/src/vcpkg C:/dev/vcpkg C:/vcpkg
  NO_DEFAULT_PATH)

if(VCPKG_CMAKE_TOOLCHAIN)
  set(CMAKE_TOOLCHAIN_FILE "${VCPKG_CMAKE_TOOLCHAIN}"
    CACHE STRING "VCPKG toolchain file")
endif()
