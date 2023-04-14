set(JSONBINPACK_CLI_PATH $<TARGET_FILE:sourcemeta_jsonbinpack_cli>)

if(WIN32)
  set(RUNNER_BIN "${CMAKE_CURRENT_SOURCE_DIR}/runner.bat")
  set(RUNNER_STDIN_BIN "${CMAKE_CURRENT_SOURCE_DIR}/runner_stdin.bat")
else()
  set(RUNNER_BIN "${CMAKE_CURRENT_SOURCE_DIR}/runner.sh")
  set(RUNNER_STDIN_BIN "${CMAKE_CURRENT_SOURCE_DIR}/runner_stdin.sh")
endif()

add_test(NAME jsonbinpack.cli_version
  COMMAND "${RUNNER_BIN}"
  "${JSONBINPACK_CLI_PATH}" 0 "${CMAKE_PROJECT_VERSION}" version)

add_test(NAME jsonbinpack.cli_default
  COMMAND "${RUNNER_BIN}"
  "${JSONBINPACK_CLI_PATH}" 1 "Usage:")

add_test(NAME jsonbinpack.cli_help
  COMMAND "${RUNNER_BIN}"
  "${JSONBINPACK_CLI_PATH}" 0 "Usage:" help)

add_test(NAME jsonbinpack.cli_unknown
  COMMAND "${RUNNER_BIN}"
  "${JSONBINPACK_CLI_PATH}" 1 "Unknown command" foobarbaz)

add_test(NAME jsonbinpack.cli_canonicalize_file
  COMMAND "${RUNNER_BIN}"
  "${JSONBINPACK_CLI_PATH}" 0 "\"enum\":"
  canonicalize "${CMAKE_CURRENT_SOURCE_DIR}/schema_boolean.json")

add_test(NAME jsonbinpack.cli_canonicalize_stdin
  COMMAND "${RUNNER_STDIN_BIN}"
  "${CMAKE_CURRENT_SOURCE_DIR}/schema_boolean.json"
  "${JSONBINPACK_CLI_PATH}" 0 "\"enum\":"
  canonicalize)

add_test(NAME jsonbinpack.cli_compile_file
  COMMAND "${RUNNER_BIN}"
  "${JSONBINPACK_CLI_PATH}" 0 "BOUNDED_MULTIPLE_8BITS_ENUM_FIXED"
  compile "${CMAKE_CURRENT_SOURCE_DIR}/schema_bounded_integer.json")

add_test(NAME jsonbinpack.cli_compile_stdin
  COMMAND "${RUNNER_STDIN_BIN}"
  "${CMAKE_CURRENT_SOURCE_DIR}/schema_bounded_integer.json"
  "${JSONBINPACK_CLI_PATH}" 0 "BOUNDED_MULTIPLE_8BITS_ENUM_FIXED"
  compile)
