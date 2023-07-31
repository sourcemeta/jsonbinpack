find_program(CLANG_TIDY_BIN NAMES clang-tidy)
if(CLANG_TIDY_BIN)
  add_custom_target(clang_tidy
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    VERBATIM
    COMMAND "${CLANG_TIDY_BIN}" "-p=${CMAKE_BINARY_DIR}"
    ${JSONBINPACK_CXX_SOURCE_FILES})
  set_target_properties(clang_tidy
    PROPERTIES FOLDER "Linters")
else()
  message(WARNING "Could not find `clang-tidy` in the system")
endif()
