cmake_minimum_required(VERSION 3.2)

if($ENV{TRAVIS_BUILD_NUMBER})
    set(VERSION_BUILD $ENV{TRAVIS_BUILD_NUMBER})
else()
    set(VERSION_BUILD 1)
endif()

set(VERSION_BUILD_MAJOR 1)
set(VERSION_BUILD_MINOR 0)

project(print_ip VERSION ${VERSION_BUILD_MAJOR}.${VERSION_BUILD_MINOR}.${VERSION_BUILD})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

set(HEADER_VERSION_PATH "${PROJECT_SOURCE_DIR}/../hw_01")

set(HEADER_PATH "${PROJECT_SOURCE_DIR}/include")
set(SOURCE_PATH "${PROJECT_SOURCE_DIR}/src")
set(TEST_PATH "${PROJECT_SOURCE_DIR}/test")

set(HEADER_FILES ${HEADER_PATH}/print.h ${HEADER_PATH}/tuple.h ${HEADER_VERSION_PATH}/include/version_library.h)

add_executable(print_ip ${SOURCE_PATH}/main.cpp ${HEADER_FILES})
add_executable(print_ip_test ${TEST_PATH}/test.cpp  ${HEADER_FILES})
add_library(version_lib STATIC IMPORTED)

set_property(TARGET version_lib PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/../build/hw_01/libhelloworld_lib.a)

target_include_directories(print_ip PRIVATE ${HEADER_PATH} ${HEADER_VERSION_PATH}/include)

set_target_properties(print_ip print_ip_test version_lib PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  LINK_LIBRARIES version_lib
)

set_target_properties(print_ip_test version_lib PROPERTIES
  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
  INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
  INCLUDE_DIRECTORIES ${HEADER_PATH}
  LINK_LIBRARIES ${Boost_LIBRARIES} 
)

install(TARGETS print_ip RUNTIME DESTINATION bin COMPONENT print_ip)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT ranihilaltor@gmail.com)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include (CPack)
set(CPACK_DEB_COMPONENT_INSTALL 1)

enable_testing()

add_test(
  NAME boost_test
  COMMAND print_ip_test
)
