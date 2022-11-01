find_program(BUNDLE_BIN NAMES bundle)
set(JSONBINPACK_BUNDLER_PATH "${PROJECT_SOURCE_DIR}/build/bundler")
if(BUNDLE_BIN)
  add_custom_target(bundler
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    VERBATIM
    COMMAND "${BUNDLE_BIN}" install --path "${JSONBINPACK_BUNDLER_PATH}")
endif()
