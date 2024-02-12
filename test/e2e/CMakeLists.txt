add_executable(jsonbinpack_e2e_test_runner runner.cc)
target_link_libraries(jsonbinpack_e2e_test_runner PRIVATE sourcemeta::jsontoolkit::json)
target_link_libraries(jsonbinpack_e2e_test_runner PRIVATE sourcemeta::jsonbinpack::canonicalizer)
target_link_libraries(jsonbinpack_e2e_test_runner PRIVATE sourcemeta::jsonbinpack::mapper)
target_link_libraries(jsonbinpack_e2e_test_runner PRIVATE sourcemeta::jsonbinpack::runtime)
set_target_properties(jsonbinpack_e2e_test_runner
  PROPERTIES FOLDER "JSON BinPack/E2E")

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

# TODO: This case regresses on real number encoding sizes
add_jsonbinpack_e2e_test(circleciblank)
add_jsonbinpack_e2e_test(circlecimatrix)
add_jsonbinpack_e2e_test(commitlint)
add_jsonbinpack_e2e_test(commitlintbasic)
add_jsonbinpack_e2e_test(epr)
add_jsonbinpack_e2e_test(eslintrc)
add_jsonbinpack_e2e_test(esmrc)
# TODO: This case regresses on real number encoding sizes
add_jsonbinpack_e2e_test(geojson)
add_jsonbinpack_e2e_test(githubfundingblank)
add_jsonbinpack_e2e_test(githubworkflow)
add_jsonbinpack_e2e_test(gruntcontribclean)
add_jsonbinpack_e2e_test(imageoptimizerwebjob)
add_jsonbinpack_e2e_test(jsonereversesort)
add_jsonbinpack_e2e_test(jsonesort)
add_jsonbinpack_e2e_test(jsonfeed)
add_jsonbinpack_e2e_test(jsonresume)
add_jsonbinpack_e2e_test(mixed-bounded-object)
add_jsonbinpack_e2e_test(netcoreproject)
add_jsonbinpack_e2e_test(nightwatch)
add_jsonbinpack_e2e_test(openweathermap)
add_jsonbinpack_e2e_test(openweatherroadrisk)
add_jsonbinpack_e2e_test(ox-test)
add_jsonbinpack_e2e_test(packagejson)
add_jsonbinpack_e2e_test(packagejsonlintrc)
add_jsonbinpack_e2e_test(sapcloudsdkpipeline)
add_jsonbinpack_e2e_test(travisnotifications)
add_jsonbinpack_e2e_test(tslintbasic)
add_jsonbinpack_e2e_test(tslintextend)
add_jsonbinpack_e2e_test(tslintmulti)
