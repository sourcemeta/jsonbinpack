set(NOA_TARGET_CLANG_TIDY_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}")

function(noa_target_clang_tidy)
  cmake_parse_arguments(NOA_TARGET_CLANG_TIDY "REQUIRED" "" "SOURCES" ${ARGN})

  if(NOA_TARGET_CLANG_TIDY_REQUIRED)
    find_program(CLANG_TIDY_BIN NAMES clang-tidy REQUIRED)
  else()
    find_program(CLANG_TIDY_BIN NAMES clang-tidy)
  endif()

  # This covers the empty list too
  if(NOT NOA_TARGET_CLANG_TIDY_SOURCES)
    message(FATAL_ERROR "You must pass file globs to analyze in the SOURCES option")
  endif()
  file(GLOB_RECURSE NOA_TARGET_CLANG_TIDY_FILES
    ${NOA_TARGET_CLANG_TIDY_SOURCES})

  set(CLANG_TIDY_CONFIG "${NOA_TARGET_CLANG_TIDY_DIRECTORY}/clang-tidy.config")
  if(CLANG_TIDY_BIN)
    add_custom_target(clang_tidy
      WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
      VERBATIM
      COMMAND "${CLANG_TIDY_BIN}" -p "${PROJECT_BINARY_DIR}"
        --config-file "${CLANG_TIDY_CONFIG}"
        ${NOA_TARGET_CLANG_TIDY_FILES}
        COMMENT "Analyzing sources using ClangTidy")
  else()
    add_custom_target(clang_tidy
      WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
      VERBATIM
      COMMAND "${CMAKE_COMMAND}" -E echo "Could not locate ClangTidy"
      COMMAND "${CMAKE_COMMAND}" -E false)
  endif()

  set_target_properties(clang_tidy PROPERTIES FOLDER "Linting")
endfunction()
