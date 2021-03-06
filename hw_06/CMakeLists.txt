cmake_minimum_required(VERSION 3.2)

if($ENV{TRAVIS_BUILD_NUMBER})
    set(VERSION_BUILD $ENV{TRAVIS_BUILD_NUMBER})
else()
    set(VERSION_BUILD 1)
endif()

set(VERSION_BUILD_MAJOR 1)
set(VERSION_BUILD_MINOR 0)

project(matrix VERSION ${VERSION_BUILD_MAJOR}.${VERSION_BUILD_MINOR}.${VERSION_BUILD})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

set(HEADER_VERSION_PATH "${PROJECT_SOURCE_DIR}/../hw_01")

set(HEADER_PATH "${PROJECT_SOURCE_DIR}/include")
set(SOURCE_PATH "${PROJECT_SOURCE_DIR}/src")
set(TEST_PATH "${PROJECT_SOURCE_DIR}/test")

set(HEADER_FILES
    ${HEADER_PATH}/matrix.hpp
    ${HEADER_PATH}/matrix_node.hpp
)

set(SOURCE_FILES 
    ${SOURCE_PATH}/main.cpp 
)

add_executable(matrix ${SOURCE_PATH}/main.cpp ${HEADER_FILES})
add_executable(matrix_test ${TEST_PATH}/test.cpp  ${HEADER_FILES})

add_library(version_lib STATIC IMPORTED)

set_property(TARGET version_lib PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/../build/hw_01/libhelloworld_lib.a)

set_target_properties(matrix version_lib PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  INCLUDE_DIRECTORIES "${HEADER_PATH};${HEADER_VERSION_PATH}/include"
  LINK_LIBRARIES version_lib
)

set_target_properties(matrix_test PROPERTIES
  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
  INCLUDE_DIRECTORIES "${HEADER_PATH};${Boost_INCLUDE_DIR}"
  LINK_LIBRARIES ${Boost_LIBRARIES} 
)

install(TARGETS matrix RUNTIME DESTINATION bin COMPONENT matrix)

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
  COMMAND matrix_test
)
