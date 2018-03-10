cmake_minimum_required(VERSION 3.2)

if($ENV{TRAVIS_BUILD_NUMBER})
    set(VERSION_BUILD $ENV{TRAVIS_BUILD_NUMBER})
    set(VERSION_BUILD_MAJOR 1)
    set(VERSION_BUILD_MINOR 0)
else()
    set(VERSION_BUILD 1)
    set(VERSION_BUILD_MAJOR 1)
    set(VERSION_BUILD_MINOR 0)
endif()

project(ip_filter VERSION ${VERSION_BUILD_MAJOR}.${VERSION_BUILD_MINOR}.${VERSION_BUILD})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

set(SOURCE_PATH "${PROJECT_SOURCE_DIR}/src")
set(TEST_PATH "${PROJECT_SOURCE_DIR}/test")

configure_file(version.h.in ${SOURCE_PATH}/version.h)

add_executable(ip_filter ${SOURCE_PATH}/main.cpp)
add_executable(ip_filter_testing ${TEST_PATH}/filter.cpp)

add_library(ip_filter_lib ${SOURCE_PATH}/library.cpp)

set_target_properties(ip_filter ip_filter_lib ip_filter_testing PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

set_target_properties(ip_filter_testing PROPERTIES
  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
  INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
  INCLUDE_DIRECTORIES ${SOURCE_PATH}
)

target_link_libraries(ip_filter 
    ip_filter_lib
)

target_link_libraries(ip_filter_testing 
    ${Boost_LIBRARIES} 
    ip_filter_lib
)




install(TARGETS ip_filter RUNTIME DESTINATION bin)


set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT ranihilaltor@gmail.com)

include (CPack)

enable_testing()

add_test(ip_header_test ip_filter_testing)
add_test(ip_filter_test ip_filter_testing)
add_test(external_test ip_filter_testing)
