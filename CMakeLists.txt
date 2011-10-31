# -*- mode: cmake; -*-
project(ec2-api)
cmake_minimum_required(VERSION 2.6.2 FATAL_ERROR)
if(POLICY CMP0011)
  cmake_policy(SET CMP0011 NEW)
endif(POLICY CMP0011)

set(EC2-API_MAJOR_VERSION 0)
set(EC2-API_MINOR_VERSION 1)
set(EC2-API_SUB_VERSION   0)
set(VERSION_SEP "-")
set(EC2-API_SHORT_VERSION "${EC2-API_MAJOR_VERSION}${VERSION_SEP}${EC2-API_MINOR_VERSION}")
set(EC2-API_VERSION "${EC2-API_SHORT_VERSION}${VERSION_SEP}${EC2-API_SUB_VERSION}")
set(EC2-API_RPM_VERSION "${EC2-API_MAJOR_VERSION}.${EC2-API_MINOR_VERSION}.${EC2-API_SUB_VERSION}")
set(VERSION_DATE "2011-09-26")

###########################################################
# Where are the additional libraries installed? Note: provide includes
# path here, subsequent checks will resolve everything else
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")

OPTION(EC2_ACCESS_KEY
  "Amazon EC2 access key (is only required for testing)"
  "")
OPTION(EC2_SECRET_KEY
  "Amazon EC2 secret key (is only required for testing)"
  "")

include ( CompilerFlags )
include ( ConfigureMacro )

# Look for the boost library we need
set(BOOST_ROOT "${ADDITIONAL_CMAKE_PATH}" CACHE PATH "Path to the Boost installation")
set(Boost_ADDITIONAL_VERSIONS "1.36" "1.36.0" "1.37" "1.37.0" "1.40" "1.40.0")
set(Boost_FIND_QUIETLY true)
set(Boost_USE_STATIC_LIBS ON)
#include(FindBoost)
find_package(Boost 1.36.0 REQUIRED COMPONENTS system regex filesystem program_options)
message(STATUS "Boost: -I${Boost_INCLUDE_DIRS} -L${Boost_LIBRARY_DIRS} -l${Boost_LIBRARIES}")

# find libbotan crypto library
Include(FindBotan)
if (BOTAN_FOUND)
  message(STATUS "Found libbotan: -I${BOTAN_INCLUDE_DIR} -l${BOTAN_LIBRARY}")
  include_directories(${BOTAN_INCLUDE_DIR})
else (BOTAN_FOUND)
  message(FATAL_ERROR "No libbotan found - you may set BOTAN_HOME.")
endif (BOTAN_FOUND)

# check for curl
IF(WIN32)
  add_definitions(-DCURL_STATICLIB)
  include(FindCURL_WIN32)
else(WIN32)
  include(FindCURL)
endif(WIN32)

include(FindCppUnit)
message(STATUS "CPPUnit: -I${CPPUNIT_INCLUDE_DIRS} -l${CPPUNIT_LIBRARY}")

include_directories(${CMAKE_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(ec2-api)
add_subdirectory(src)

# enable unit testing
include(CTest)
enable_testing()
add_subdirectory(tests)

### print some output for the user
message("")
message("        ***** Configuration parameters *****")
message("             prefix: ${CMAKE_INSTALL_PREFIX}")

# add some files to the installation target
INSTALL(FILES README INSTALL COPYRIGHT DESTINATION
  share/doc/ec2-api-${V_MAJOR}-${V_MINOR}
)

# CPACK packaging
INCLUDE(InstallRequiredSystemLibraries)
set(CPACK_SOURCE_GENERATOR "TGZ;TBZ2")

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Gridlicense Demo Tools")
set(CPACK_PACKAGE_VENDOR              "Fraunhofer ITWM")
set(CPACK_PACKAGE_CONTACT             "Kai Krueger <kai.krueger@itwm.fraunhofer.de>")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER   "Kai Krueger <kai.krueger@itwm.fraunhofer.de>")
set(CPACK_PACKAGE_DESCRIPTION_FILE    "${CMAKE_CURRENT_SOURCE_DIR}/README")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYRIGHT")
set(CPACK_PACKAGE_VERSION_MAJOR ${V_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${V_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${V_PATCH})
set(CPACK_PACKAGE_INSTALL_DIRECTORY "${PROJECT_NAME}-${V_MAJOR}.${V_MINOR}")

set(CPACK_SOURCE_IGNORE_FILES "/CVS/;/.svn/;.swp$;.#;/#;.*~;cscope.*;build.*")

if(WIN32 AND NOT UNIX)
  set(CPACK_GENERATOR "NSIS")
  set(CPACK_NSIS_PACKAGE_NAME "Gridlicense Demo Tools")
  # set(CPACK_PACKAGE_EXECUTABLES "gui4" "Grid License Demo Frontend")
  set(CPACK_PACKAGE_DEFAULT_LOCATION ${INSTALL_DIR})

  # sure there is at least one set of four (4) backlasshes.
  set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\gui4.exe")
  set(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} Gridlicense Demo Tools")
  set(CPACK_NSIS_HELP_LINK    "http://www.itwm.fraunhofer.de/")
  set(CPACK_NSIS_URL_INFO_ABOUT "http://www.itwm.fraunhofer.de/abteilungen/hpc.html")
  set(CPACK_NSIS_CONTACT "Kai Krueger <kai.krueger@itwm.fraunhofer.de>")
  set(CPACK_NSIS_MODIFY_PATH ON)
  # set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "${CMAKE_PROJECT_NAME}-${EWS_VERSION}")
  # set(CPACK_NSIS_MENU_LINKS "${EWS_WEBSITE}" "Homepage for ${EWS_APP_NAME}")
  set(CPACK_NSIS_DEFINES "  !define MUI_WELCOMEPAGE_TITLE_3LINES 1
    !define MUI_FINISHPAGE_TITLE_3LINES 1")
else(WIN32 AND NOT UNIX)
  #set(CPACK_SET_DESTDIR On)
  set(CPACK_SOURCE_STRIP_FILES "")
  set(CPACK_GENERATOR "TGZ;TBZ2;TZ;DEB;RPM")
  set(CPACK_RPM_PACKAGE_RELOCATABLE 1)
endif(WIN32 AND NOT UNIX)
include(CPack)

# Local variables:
#   tab-width: 2
#   c-indent-level: 2
#   c-basic-offset: 2
#   project-name: ec2-api
#  End:
