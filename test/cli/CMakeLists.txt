set(JSONBINPACK_CLI_PATH $<TARGET_FILE:sourcemeta_jsonbinpack_cli>)

if(WIN32)
  set(RUNNER_BIN "${CMAKE_CURRENT_SOURCE_DIR}/runner.bat")
  set(RUNNER_STDIN_BIN "${CMAKE_CURRENT_SOURCE_DIR}/runner_stdin.bat")
  set(SAME_BIN "${CMAKE_CURRENT_SOURCE_DIR}/same.bat")
  set(SAME_STDIN_BIN "${CMAKE_CURRENT_SOURCE_DIR}/same_stdin.bat")
else()
  set(RUNNER_BIN "${CMAKE_CURRENT_SOURCE_DIR}/runner.sh")
  set(RUNNER_STDIN_BIN "${CMAKE_CURRENT_SOURCE_DIR}/runner_stdin.sh")
  set(SAME_BIN "${CMAKE_CURRENT_SOURCE_DIR}/same.sh")
  set(SAME_STDIN_BIN "${CMAKE_CURRENT_SOURCE_DIR}/same_stdin.sh")
endif()

add_test(NAME JSONBinPack.cli_version
  COMMAND "${RUNNER_BIN}"
  "${JSONBINPACK_CLI_PATH}" 0 "${CMAKE_PROJECT_VERSION}" version)

add_test(NAME JSONBinPack.cli_default
  COMMAND "${RUNNER_BIN}"
  "${JSONBINPACK_CLI_PATH}" 1 "Usage:")

add_test(NAME JSONBinPack.cli_help
  COMMAND "${RUNNER_BIN}"
  "${JSONBINPACK_CLI_PATH}" 0 "Usage:" help)

add_test(NAME JSONBinPack.cli_unknown
  COMMAND "${RUNNER_BIN}"
  "${JSONBINPACK_CLI_PATH}" 1 "Unknown command" foobarbaz)

add_test(NAME JSONBinPack.cli_canonicalize_file
  COMMAND "${RUNNER_BIN}"
  "${JSONBINPACK_CLI_PATH}" 0 "\"enum\":"
  canonicalize "${CMAKE_CURRENT_SOURCE_DIR}/schema_boolean.json")

add_test(NAME JSONBinPack.cli_canonicalize_stdin
  COMMAND "${RUNNER_STDIN_BIN}"
  "${CMAKE_CURRENT_SOURCE_DIR}/schema_boolean.json"
  "${JSONBINPACK_CLI_PATH}" 0 "\"enum\":"
  canonicalize)

add_test(NAME JSONBinPack.cli_compile_file
  COMMAND "${RUNNER_BIN}"
  "${JSONBINPACK_CLI_PATH}" 0 "BOUNDED_MULTIPLE_8BITS_ENUM_FIXED"
  compile "${CMAKE_CURRENT_SOURCE_DIR}/schema_bounded_integer.json")

add_test(NAME JSONBinPack.cli_compile_stdin
  COMMAND "${RUNNER_STDIN_BIN}"
  "${CMAKE_CURRENT_SOURCE_DIR}/schema_bounded_integer.json"
  "${JSONBINPACK_CLI_PATH}" 0 "BOUNDED_MULTIPLE_8BITS_ENUM_FIXED"
  compile)

# Encoding Schema

add_test(NAME JSONBinPack.cli_encode_encoding_schema_arg
  COMMAND "${SAME_BIN}" "${JSONBINPACK_CLI_PATH}"
  "${CMAKE_CURRENT_SOURCE_DIR}/instance_integer.bin" encode
  "${CMAKE_CURRENT_SOURCE_DIR}/instance_integer_encoding.json"
  "${CMAKE_CURRENT_SOURCE_DIR}/instance_integer.json")

add_test(NAME JSONBinPack.cli_decode_encoding_schema_arg
  COMMAND "${SAME_BIN}" "${JSONBINPACK_CLI_PATH}"
  "${CMAKE_CURRENT_SOURCE_DIR}/instance_integer.json" decode
  "${CMAKE_CURRENT_SOURCE_DIR}/instance_integer_encoding.json"
  "${CMAKE_CURRENT_SOURCE_DIR}/instance_integer.bin")

add_test(NAME JSONBinPack.cli_encode_encoding_schema_stdin
  COMMAND "${SAME_STDIN_BIN}" "${JSONBINPACK_CLI_PATH}"
  "${CMAKE_CURRENT_SOURCE_DIR}/instance_integer.bin"
  "${CMAKE_CURRENT_SOURCE_DIR}/instance_integer.json"
  encode "${CMAKE_CURRENT_SOURCE_DIR}/instance_integer_encoding.json")

add_test(NAME JSONBinPack.cli_decode_encoding_schema_stdin
  COMMAND "${SAME_STDIN_BIN}" "${JSONBINPACK_CLI_PATH}"
  "${CMAKE_CURRENT_SOURCE_DIR}/instance_integer.json"
  "${CMAKE_CURRENT_SOURCE_DIR}/instance_integer.bin"
  decode "${CMAKE_CURRENT_SOURCE_DIR}/instance_integer_encoding.json")

# JSON Schema

add_test(NAME JSONBinPack.cli_encode_json_schema_arg
  COMMAND "${SAME_BIN}" "${JSONBINPACK_CLI_PATH}"
  "${CMAKE_CURRENT_SOURCE_DIR}/instance_integer.bin" encode
  "${CMAKE_CURRENT_SOURCE_DIR}/instance_integer_schema.json"
  "${CMAKE_CURRENT_SOURCE_DIR}/instance_integer.json")

add_test(NAME JSONBinPack.cli_decode_json_schema_arg
  COMMAND "${SAME_BIN}" "${JSONBINPACK_CLI_PATH}"
  "${CMAKE_CURRENT_SOURCE_DIR}/instance_integer.json" decode
  "${CMAKE_CURRENT_SOURCE_DIR}/instance_integer_schema.json"
  "${CMAKE_CURRENT_SOURCE_DIR}/instance_integer.bin")

add_test(NAME JSONBinPack.cli_encode_json_schema_stdin
  COMMAND "${SAME_STDIN_BIN}" "${JSONBINPACK_CLI_PATH}"
  "${CMAKE_CURRENT_SOURCE_DIR}/instance_integer.bin"
  "${CMAKE_CURRENT_SOURCE_DIR}/instance_integer.json"
  encode "${CMAKE_CURRENT_SOURCE_DIR}/instance_integer_schema.json")

add_test(NAME JSONBinPack.cli_decode_json_schema_stdin
  COMMAND "${SAME_STDIN_BIN}" "${JSONBINPACK_CLI_PATH}"
  "${CMAKE_CURRENT_SOURCE_DIR}/instance_integer.json"
  "${CMAKE_CURRENT_SOURCE_DIR}/instance_integer.bin"
  decode "${CMAKE_CURRENT_SOURCE_DIR}/instance_integer_schema.json")
