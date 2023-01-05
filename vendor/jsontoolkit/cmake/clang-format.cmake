file(GLOB_RECURSE JSONTOOLKIT_CXX_FILES
  src/*.h src/*.cc include/*.h
  test/*.cc test/*.h
  contrib/*.cc contrib/*.h)
find_program(CLANG_FORMAT_BIN NAMES clang-format)
if(CLANG_FORMAT_BIN)
  add_custom_target(clang_format
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    VERBATIM
    COMMAND "${CLANG_FORMAT_BIN}" --style=file
    -i ${JSONTOOLKIT_CXX_FILES})
  add_custom_target(clang_format_test
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    VERBATIM
    COMMAND "${CLANG_FORMAT_BIN}" --style=file
    --dry-run -Werror
    -i ${JSONTOOLKIT_CXX_FILES})
else()
  message(WARNING "clang-format: command not found")
endif()
