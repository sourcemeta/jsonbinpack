set(JSONBINPACK_CLI_PATH $<TARGET_FILE:sourcemeta::jsonbinpack_cli>)

add_test(NAME jsonbinpack.cli_version
  COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/runner.sh"
  "${JSONBINPACK_CLI_PATH}" 0 "${CMAKE_PROJECT_VERSION}" version)

add_test(NAME jsonbinpack.cli_default
  COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/runner.sh"
  "${JSONBINPACK_CLI_PATH}" 1 "Usage:")

add_test(NAME jsonbinpack.cli_help
  COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/runner.sh"
  "${JSONBINPACK_CLI_PATH}" 0 "Usage:" help)

add_test(NAME jsonbinpack.cli_unknown
  COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/runner.sh"
  "${JSONBINPACK_CLI_PATH}" 1 "Unknown command" foobarbaz)

add_test(NAME jsonbinpack.cli_canonicalize_file
  COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/runner.sh"
  "${JSONBINPACK_CLI_PATH}" 0 "\"enum\":"
  canonicalize "${CMAKE_CURRENT_SOURCE_DIR}/schema.json")
