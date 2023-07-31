find_program(SHELLCHECK_BIN NAMES shellcheck)
if(SHELLCHECK_BIN)
  add_custom_target(shellcheck
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    VERBATIM
    COMMAND "${SHELLCHECK_BIN}" ${JSONBINPACK_SH_SOURCE_FILES})
  set_target_properties(shellcheck
    PROPERTIES FOLDER "Linters")
else()
  message(WARNING "Could not find `shellcheck` in the system")
endif()
