# -*- mode: cmake; -*-

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${Boost_INCLUDE_DIR})
include_directories(${BOTAN_INCLUDE_DIR})
include_directories(${CURL_INCLUDE_DIR})

set(ec2_hdrs ec2.hpp
  RequestCore.hpp
  CurlRequest.hpp
  ResponseCore.hpp
  CurlCallback.hpp
  RequestObserver.hpp
  SimpleRequestObserver.hpp
  http_response.hpp
)
set(ec2_srcs ec2.cpp
  RequestCore.cpp
  CurlRequest.cpp
  ResponseCore.cpp
  CurlCallback.cpp
  )

add_library(ec2api ${ec2_srcs})
target_link_libraries(ec2api ${BOTAN_LIBRARY})

set(srcs sample.cpp)

add_executable(sample ${srcs})
target_link_libraries(sample ec2api)
target_link_libraries(sample ${Boost_LIBRARIES})
target_link_libraries(sample uuid)
# target_link_libraries(sample ${Boost_DATE_TIME_LIBRARY})
# target_link_libraries(sample ${Boost_SYSTEM_LIBRARY})
if(WIN32)
  target_link_libraries(sample ${CURL_STATIC_LIBRARIES})
else(WIN32)
  target_link_libraries(sample ${CURL_LIBRARIES} ${CURL_IMP_LIBRARY})
endif(WIN32)


add_subdirectory(parse)
