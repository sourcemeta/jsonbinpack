find_program(BUNDLE_BIN NAMES bundle)
if(BUNDLE_BIN)
  add_custom_target(jekyll
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    VERBATIM
    COMMAND ${BUNDLE_BIN} exec jekyll build
      --source ${JSONBINPACK_WEBSITE_SRC} --destination ${JSONBINPACK_WEBSITE_OUT})
endif()
