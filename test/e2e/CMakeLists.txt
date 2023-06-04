add_executable(jsonbinpack_e2e_test_runner runner.cc)
target_link_libraries(jsonbinpack_e2e_test_runner PRIVATE sourcemeta_jsontoolkit_json)
target_link_libraries(jsonbinpack_e2e_test_runner PRIVATE sourcemeta_jsonbinpack_canonicalizer)
target_link_libraries(jsonbinpack_e2e_test_runner PRIVATE sourcemeta_jsonbinpack_mapper)
target_link_libraries(jsonbinpack_e2e_test_runner PRIVATE sourcemeta_jsonbinpack_parser)
target_link_libraries(jsonbinpack_e2e_test_runner PRIVATE sourcemeta_jsonbinpack_encoder)
target_link_libraries(jsonbinpack_e2e_test_runner PRIVATE sourcemeta_jsonbinpack_decoder)

macro(add_jsonbinpack_e2e_test_schemaless name)
  add_test(NAME e2e.${name}.schema-less
    COMMAND "$<TARGET_FILE:jsonbinpack_e2e_test_runner>"
    "${CMAKE_CURRENT_SOURCE_DIR}/${name}/document.json"
    "${CMAKE_CURRENT_SOURCE_DIR}/${name}/schema-less")
endmacro()

macro(add_jsonbinpack_e2e_test name)
  add_jsonbinpack_e2e_test_schemaless(${name})
  # TODO: Test schema-driven too
endmacro()

add_jsonbinpack_e2e_test(circleciblank)
add_jsonbinpack_e2e_test(circlecimatrix)

# TODO: Add remaining e2e tests from benchmark paper
