cmake_minimum_required(VERSION 3.2)

if($ENV{TRAVIS_BUILD_NUMBER})
    set(VERSION_BUILD $ENV{TRAVIS_BUILD_NUMBER})
else()
    set(VERSION_BUILD 1)
endif()

set(VERSION_BUILD_MAJOR 1)
set(VERSION_BUILD_MINOR 0)


project(ip_filter VERSION ${VERSION_BUILD_MAJOR}.${VERSION_BUILD_MINOR}.${VERSION_BUILD})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

set(HEADER_PATH "${PROJECT_SOURCE_DIR}/include")
set(SOURCE_PATH "${PROJECT_SOURCE_DIR}/src")
set(TEST_PATH "${PROJECT_SOURCE_DIR}/test")

set(HEADER_FILES ${HEADER_PATH}/filter.h)

add_executable(ip_filter ${SOURCE_PATH}/main.cpp ${HEADER_FILES})
add_executable(ip_filter_testing ${TEST_PATH}/test.cpp ${HEADER_FILES})

set_target_properties(ip_filter ip_filter_testing PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  INCLUDE_DIRECTORIES ${HEADER_PATH} 
)

set_target_properties(ip_filter_testing PROPERTIES
  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
  INCLUDE_DIRECTORIES "${Boost_INCLUDE_DIR};${HEADER_PATH}"
  LINK_LIBRARIES ${Boost_LIBRARIES}
)

install(TARGETS ip_filter RUNTIME DESTINATION bin COMPONENT ip_filter)


set(CPACK_GENERATOR DEB)


set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT ranihilaltor@gmail.com)

include (CPack)
set(CPACK_DEB_COMPONENT_INSTALL 1)

enable_testing()

add_test(
  NAME boost_test
  COMMAND ip_filter_testing
)
