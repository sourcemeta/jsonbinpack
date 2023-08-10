find_package(Doxygen)
if(DOXYGEN_FOUND)
  set(DOXYGEN_IN "${PROJECT_SOURCE_DIR}/doxygen/Doxyfile.in")
  set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
  configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)
  add_custom_target(doxygen
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    VERBATIM
    COMMAND "${CMAKE_COMMAND}" -E make_directory "${JSONBINPACK_WEBSITE_OUT}"
    COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}")
  set_target_properties(doxygen
    PROPERTIES FOLDER "Website")
else()
  message(WARNING "Could not find `doxygen` in the system")
endif()
