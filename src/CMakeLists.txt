# -*- mode: cmake; -*-

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${Boost_INCLUDE_DIR})
#include_directories(${BOTAN_INCLUDE_DIR})
#include_directories(${CURL_INCLUDE_DIR})

add_library(ec2cmd ec2Command.cpp parse_cmdline.cpp options.cpp)

add_executable(ec2-cmd ec2-cmd.cpp )
target_link_libraries(ec2-cmd ec2cmd ec2api)
target_link_libraries(ec2-cmd ${Boost_LIBRARIES})
target_link_libraries(ec2-cmd uuid)
if(WIN32)
  target_link_libraries(ec2-cmd ${CURL_STATIC_LIBRARIES})
else(WIN32)
  target_link_libraries(ec2-cmd ${CURL_LIBRARIES} ${CURL_IMP_LIBRARY})
endif(WIN32)

# ec2-describe-images
add_executable(ec2-describe-images ec2-describe-images.cpp)
target_link_libraries(ec2-describe-images ec2cmd ec2api)
target_link_libraries(ec2-describe-images ${Boost_LIBRARIES})
target_link_libraries(ec2-describe-images uuid)
if(WIN32)
  target_link_libraries(ec2-describe-images ${CURL_STATIC_LIBRARIES})
else(WIN32)
  target_link_libraries(ec2-describe-images ${CURL_LIBRARIES} ${CURL_IMP_LIBRARY})
endif(WIN32)


# ec2-describe-instances
add_executable(ec2-describe-instances ec2-describe-instances.cpp)
target_link_libraries(ec2-describe-instances ec2cmd ec2api)
target_link_libraries(ec2-describe-instances ${Boost_LIBRARIES})
target_link_libraries(ec2-describe-instances uuid)
if(WIN32)
  target_link_libraries(ec2-describe-instances ${CURL_STATIC_LIBRARIES})
else(WIN32)
  target_link_libraries(ec2-describe-instances ${CURL_LIBRARIES} ${CURL_IMP_LIBRARY})
endif(WIN32)

# ec2-run-instances
add_executable(ec2-run-instances ec2-run-instances.cpp)
target_link_libraries(ec2-run-instances ec2cmd ec2api)
target_link_libraries(ec2-run-instances ${Boost_LIBRARIES})
target_link_libraries(ec2-run-instances uuid)
if(WIN32)
  target_link_libraries(ec2-run-instances ${CURL_STATIC_LIBRARIES})
else(WIN32)
  target_link_libraries(ec2-run-instances ${CURL_LIBRARIES} ${CURL_IMP_LIBRARY})
endif(WIN32)

# ec2-terminate-instances
add_executable(ec2-terminate-instances ec2-terminate-instances.cpp)
target_link_libraries(ec2-terminate-instances ec2cmd ec2api)
target_link_libraries(ec2-terminate-instances ${Boost_LIBRARIES})
target_link_libraries(ec2-terminate-instances uuid)
if(WIN32)
  target_link_libraries(ec2-terminate-instances ${CURL_STATIC_LIBRARIES})
else(WIN32)
  target_link_libraries(ec2-terminate-instances ${CURL_LIBRARIES} ${CURL_IMP_LIBRARY})
endif(WIN32)
