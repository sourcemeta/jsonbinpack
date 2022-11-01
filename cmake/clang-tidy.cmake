find_program(CLANG_TIDY_BIN NAMES clang-tidy)
if(CLANG_TIDY_BIN)
  add_custom_target(clang_tidy
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    VERBATIM
    COMMAND "${CLANG_TIDY_BIN}" "-p=${CMAKE_BINARY_DIR}"
    ${JSONBINPACK_CXX_SOURCE_FILES})
endif()
