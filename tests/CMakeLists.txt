# -*- mode: cmake; -*-
#
# Needed for testconfig.hpp
# Build the test configuration
myconfigure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/testconfig.hpp.in
  ${CMAKE_CURRENT_BINARY_DIR}/testconfig.hpp
  )

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CPPUNIT_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})
link_directories(${CPPUNIT_LIBRARY_DIRS})

set(ec2test_src
  parsertest.cpp
  livetest.cpp
  )

add_executable(ec2testsuite ${ec2test_src} main.cpp)

add_test(ec2testsuite ${CMAKE_CURRENT_BINARY_DIR}/ec2testsuite)

target_link_libraries(ec2testsuite ec2api)
target_link_libraries(ec2testsuite ${Boost_LIBRARIES})
target_link_libraries(ec2testsuite ${CPPUNIT_LIBRARY})
target_link_libraries(ec2testsuite ${CURL_STATIC_LIBRARIES} ${CURL_LIBRARY})
target_link_libraries(ec2testsuite ${BOTAN_LIBRARY})
target_link_libraries(ec2testsuite uuid)
