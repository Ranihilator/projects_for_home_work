cmake_minimum_required(VERSION 3.2)

if($ENV{TRAVIS_BUILD_NUMBER})
    set(VERSION_BUILD $ENV{TRAVIS_BUILD_NUMBER})
else()
    set(VERSION_BUILD 1)
endif()

set(VERSION_BUILD_MAJOR 1)
set(VERSION_BUILD_MINOR 0)

project(bulk VERSION ${VERSION_BUILD_MAJOR}.${VERSION_BUILD_MINOR}.${VERSION_BUILD})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

set(HEADER_VERSION_PATH "${PROJECT_SOURCE_DIR}/../hw_01")

set(HEADER_PATH "${PROJECT_SOURCE_DIR}/include")
set(SOURCE_PATH "${PROJECT_SOURCE_DIR}/src")
set(TEST_PATH "${PROJECT_SOURCE_DIR}/test")

set(HEADER_FILES "${HEADER_PATH}/bulk.h"
                 "${HEADER_PATH}/parser.h"
                 "${HEADER_PATH}/output/log.h"
                 "${HEADER_PATH}/output/file_log.h"
                 "${HEADER_PATH}/output/console_log.h"
)

set(SOURCE_FILES "${SOURCE_PATH}/bulk.cpp"
                 "${SOURCE_PATH}/parser.cpp"
                 "${SOURCE_PATH}/output/file_log.cpp"
                 "${SOURCE_PATH}/output/console_log.cpp"
)

add_executable(bulk ${SOURCE_PATH}/main.cpp ${HEADER_FILES} ${SOURCE_FILES})
add_executable(bulk_test ${TEST_PATH}/test.cpp ${HEADER_FILES} ${SOURCE_FILES})

add_library(version_lib STATIC IMPORTED)

set_property(TARGET version_lib PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/../build/hw_01/libhelloworld_lib.a)

set_target_properties(bulk version_lib PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  INCLUDE_DIRECTORIES "${HEADER_PATH};${HEADER_VERSION_PATH}/include"
  LINK_LIBRARIES version_lib
)

set_target_properties(bulk_test PROPERTIES
  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
  INCLUDE_DIRECTORIES "${HEADER_PATH};${Boost_INCLUDE_DIR}"
  LINK_LIBRARIES ${Boost_LIBRARIES} 
)

install(TARGETS bulk RUNTIME DESTINATION bin COMPONENT bulk)

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
  COMMAND bulk_test
)
