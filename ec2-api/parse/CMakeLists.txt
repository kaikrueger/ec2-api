# -*- mode: cmake; -*-

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${Boost_INCLUDE_DIR})

set(ec2xml_hdrs
  TerminateInstances.hpp
)
set(ec2xml_srcs
  sample.cpp
)

add_executable(xmlsample ${ec2xml_srcs})
target_link_libraries(xmlsample ${Boost_DATE_TIME_LIBRARY})
target_link_libraries(xmlsample ${Boost_SYSTEM_LIBRARY})
