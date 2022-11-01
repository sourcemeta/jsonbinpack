find_program(CLANG_FORMAT_BIN NAMES clang-format)
if(CLANG_FORMAT_BIN)
  add_custom_target(clang_format
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    VERBATIM
    COMMAND "${CLANG_FORMAT_BIN}" --style=file
    -i ${JSONBINPACK_CXX_SOURCE_FILES})

  add_custom_target(clang_format_test
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    VERBATIM
    COMMAND "${CLANG_FORMAT_BIN}" --style=file
    --dry-run -Werror
    -i ${JSONBINPACK_CXX_SOURCE_FILES})
else()
  message(WARNING "Could not find `clang-format` in the system")
endif()
