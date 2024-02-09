set(URIPARSER_BUILD_DOCS OFF CACHE BOOL "omit docs")
set(URIPARSER_BUILD_TESTS OFF CACHE BOOL "omit tests")
set(URIPARSER_BUILD_TOOLS OFF CACHE BOOL "omit tools")
set(URIPARSER_BUILD_TOOLS OFF CACHE BOOL "omit tools")
set(URIPARSER_ENABLE_INSTALL OFF CACHE BOOL "omit installation")

add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/uriparser")
add_library(uriparser::uriparser ALIAS uriparser)
include(GNUInstallDirs)
install(TARGETS uriparser
  EXPORT uriparser
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/uriparser"
    COMPONENT sourcemeta_jsontoolkit_dev
  PRIVATE_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/uriparser"
    COMPONENT sourcemeta_jsontoolkit_dev
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    COMPONENT sourcemeta_jsontoolkit
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    COMPONENT sourcemeta_jsontoolkit
    NAMELINK_COMPONENT sourcemeta_jsontoolkit_dev
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    COMPONENT sourcemeta_jsontoolkit_dev)
install(EXPORT uriparser
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/uriparser"
  NAMESPACE uriparser::
  COMPONENT sourcemeta_jsontoolkit_dev)

set(UriParser_FOUND ON)
