set(JSONTOOLKIT_JSON_META_HEADERS
  include/jsontoolkit/json/read.h
  include/jsontoolkit/json/write.h
  include/jsontoolkit/json/iterators.h)
set(JSONTOOLKIT_JSON_BACKEND_HEADERS
  include/jsontoolkit/json/${JSONTOOLKIT_BACKEND}/common.h
  include/jsontoolkit/json/${JSONTOOLKIT_BACKEND}/read.h
  include/jsontoolkit/json/${JSONTOOLKIT_BACKEND}/write.h
  include/jsontoolkit/json/${JSONTOOLKIT_BACKEND}/iterators.h)
add_library(sourcemeta_jsontoolkit_json
  INTERFACE ${JSONTOOLKIT_JSON_META_HEADERS} ${JSONTOOLKIT_JSON_BACKEND_HEADERS})
add_library(sourcemeta::jsontoolkit::json ALIAS sourcemeta_jsontoolkit_json)
set_target_properties(sourcemeta_jsontoolkit_json
  PROPERTIES PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/include/jsontoolkit/json.h"
  OUTPUT_NAME jsontoolkit-json
  EXPORT_NAME jsontoolkit::json)
target_include_directories(sourcemeta_jsontoolkit_json
  INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
include("${PROJECT_SOURCE_DIR}/cmake/${JSONTOOLKIT_BACKEND}.cmake")
string(TOUPPER ${JSONTOOLKIT_BACKEND} UPPER_JSONTOOLKIT_BACKEND)
target_compile_definitions(sourcemeta_jsontoolkit_json INTERFACE
  JSONTOOLKIT_BACKEND_${UPPER_JSONTOOLKIT_BACKEND})
target_link_libraries(sourcemeta_jsontoolkit_json INTERFACE
  ${JSONTOOLKIT_BACKEND})

# Installation
install(TARGETS sourcemeta_jsontoolkit_json
  EXPORT sourcemeta_jsontoolkit_json
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT jsontoolkit
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/jsontoolkit" COMPONENT jsontoolkit)
install(FILES ${JSONTOOLKIT_JSON_META_HEADERS}
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/jsontoolkit/json"
  COMPONENT jsontoolkit)
install(FILES ${JSONTOOLKIT_JSON_BACKEND_HEADERS}
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/jsontoolkit/json/${JSONTOOLKIT_BACKEND}"
  COMPONENT jsontoolkit)
