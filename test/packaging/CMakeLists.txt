# TODO: Get install path from a variable?
add_test(NAME packaging.find_package_configure COMMAND
  "${CMAKE_COMMAND}"
  -S "${CMAKE_CURRENT_SOURCE_DIR}/find_package"
  -B "${CMAKE_CURRENT_BINARY_DIR}/find_package"
  "-DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}"
  "-DCMAKE_PREFIX_PATH:PATH=${CMAKE_PREFIX_PATH};${PROJECT_SOURCE_DIR}/build/dist"
  "-DCMAKE_TOOLCHAIN_FILE:PATH=${CMAKE_TOOLCHAIN_FILE}")
add_test(NAME packaging.find_package_build COMMAND
  "${CMAKE_COMMAND}"
  --build "${CMAKE_CURRENT_BINARY_DIR}/find_package"
  --config "${CMAKE_BUILD_TYPE}")
set_tests_properties(packaging.find_package_build
  PROPERTIES DEPENDS packaging.find_package_configure)
