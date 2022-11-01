find_package(Doxygen)
if(DOXYGEN_FOUND)
  set(DOXYGEN_IN "${PROJECT_SOURCE_DIR}/Doxyfile.in")
  set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
  configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)
  add_custom_target(doxygen
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    VERBATIM
    COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}")
else()
  message(WARNING "Could not find `doxygen` in the system")
endif()
