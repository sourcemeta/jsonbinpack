set(NOA_TARGET_CLANG_FORMAT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}")

function(noa_target_clang_format)
  cmake_parse_arguments(NOA_TARGET_CLANG_FORMAT "REQUIRED" "" "SOURCES" ${ARGN})

  if(NOA_TARGET_CLANG_FORMAT_REQUIRED)
    find_program(CLANG_FORMAT_BIN NAMES clang-format REQUIRED)
  else()
    find_program(CLANG_FORMAT_BIN NAMES clang-format)
  endif()

  # This covers the empty list too
  if(NOT NOA_TARGET_CLANG_FORMAT_SOURCES)
    message(FATAL_ERROR "You must pass file globs to format in the SOURCES option")
  endif()
  file(GLOB_RECURSE NOA_TARGET_CLANG_FORMAT_FILES
    ${NOA_TARGET_CLANG_FORMAT_SOURCES})

  set(CLANG_FORMAT_CONFIG "${NOA_TARGET_CLANG_FORMAT_DIRECTORY}/clang-format.config")
  if(CLANG_FORMAT_BIN)
    add_custom_target(clang_format
      WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
      VERBATIM
      COMMAND "${CLANG_FORMAT_BIN}" "--style=file:${CLANG_FORMAT_CONFIG}"
        -i ${NOA_TARGET_CLANG_FORMAT_FILES}
      COMMENT "Formatting sources using ClangFormat")
    add_custom_target(clang_format_test
      WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
      VERBATIM
      COMMAND "${CLANG_FORMAT_BIN}" "--style=file:${CLANG_FORMAT_CONFIG}"
        --dry-run -Werror
        -i ${NOA_TARGET_CLANG_FORMAT_FILES}
      COMMENT "Checking for ClangFormat compliance")
  else()
    add_custom_target(clang_format
      WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
      VERBATIM
      COMMAND "${CMAKE_COMMAND}" -E echo "Could not locate ClangFormat"
      COMMAND "${CMAKE_COMMAND}" -E false)
    add_custom_target(clang_format_test
      WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
      VERBATIM
      COMMAND "${CMAKE_COMMAND}" -E echo "Could not locate ClangFormat"
      COMMAND "${CMAKE_COMMAND}" -E false)
  endif()

  set_target_properties(clang_format clang_format_test PROPERTIES FOLDER "Formatting")
endfunction()
