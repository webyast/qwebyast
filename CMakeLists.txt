cmake_minimum_required(VERSION 2.8)

set(PACKAGE "qwebyast")
project(${PACKAGE})
set( CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules )

include( ${CMAKE_SOURCE_DIR}/VERSION.cmake )
set ( VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}" )
set(CPACK_PACKAGE_VENDOR "Novell Inc.")
set(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})

set( CPACK_GENERATOR "TBZ2")
set( CPACK_SOURCE_GENERATOR "TBZ2")
set( CPACK_SOURCE_PACKAGE_FILE_NAME "${PACKAGE}-${VERSION}" )

# The following components are regex's to match anywhere (unless anchored)
# in absolute path + filename to find files or directories to be excluded
# from source tarball.
set (CPACK_SOURCE_IGNORE_FILES
"/CVS/;/.svn/;/.git/;/.libs/;/.deps/;.swp$;.#;/#;/build/"
"~$"
"\\\\.cvsignore$"
#"/package"
"Makefile\\\\.in$"
)

include(CPack)

find_package(Qt4 REQUIRED)

MESSAGE(STATUS "$LIB is ${LIB}" )
# Library
IF ( DEFINED LIB )
  SET ( LIB_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/${LIB}" )
ELSE ( DEFINED  LIB )
  SET ( LIB_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}" )
ENDIF ( DEFINED  LIB )
MESSAGE(STATUS "Libraries will be installed in ${LIB_INSTALL_DIR}" )



add_subdirectory( icons )
add_subdirectory( src )

message(STATUS "Writing spec file...")
configure_file(${CMAKE_SOURCE_DIR}/${PACKAGE}.spec.in ${CMAKE_BINARY_DIR}/package/${PACKAGE}.spec @ONLY)

add_custom_target( svncheck
  command cd $(CMAKE_SOURCE_DIR) && ! LC_ALL=C svn status --show-updates --quiet | grep -v '^Status against revision'
)

set( AUTOBUILD_COMMAND
  COMMAND ${CMAKE_MAKE_PROGRAM} package_source
  COMMAND ${CMAKE_COMMAND} -E copy ${CPACK_SOURCE_PACKAGE_FILE_NAME}.tar.bz2 ${CMAKE_BINARY_DIR}/package
  COMMAND ${CMAKE_COMMAND} -E remove ${CPACK_SOURCE_PACKAGE_FILE_NAME}.tar.bz2
  COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/package/${PACKAGE}.changes" "${CMAKE_BINARY_DIR}/package/${PACKAGE}.changes"
)

add_custom_target( srcpackage_local
  ${AUTOBUILD_COMMAND}
)

add_custom_target( srcpackage
  COMMAND ${CMAKE_MAKE_PROGRAM} svncheck
  ${AUTOBUILD_COMMAND}
)
