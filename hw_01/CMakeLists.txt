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

project(helloworld VERSION ${VERSION_BUILD_MAJOR}.${VERSION_BUILD_MINOR}.${VERSION_BUILD})

find_package(Boost COMPONENTS unit_test_framework REQUIRED) 

set(HEADER_PATH "${PROJECT_SOURCE_DIR}/include")
set(SOURCE_PATH "${PROJECT_SOURCE_DIR}/src")
set(TEST_PATH "${PROJECT_SOURCE_DIR}/test")

configure_file(version.h.in ${HEADER_PATH}/version.h)

set(HEADER_FILES ${HEADER_PATH}/version.h ${HEADER_PATH}/library.h)

add_executable(helloworld_cli ${SOURCE_PATH}/main.cpp ${HEADER_FILES})
add_executable(helloworld_test ${TEST_PATH}/test.cpp ${HEADER_FILES})
add_library(helloworld_lib ${SOURCE_PATH}/library.cpp ${HEADER_FILES})


target_include_directories(helloworld_cli PRIVATE ${HEADER_PATH})
target_include_directories(helloworld_lib PRIVATE ${HEADER_PATH})


set_target_properties(helloworld_cli helloworld_lib helloworld_test PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

set_target_properties(helloworld_test PROPERTIES
  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
  INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
  INCLUDE_DIRECTORIES ${HEADER_PATH}
)

target_link_libraries(helloworld_cli
    helloworld_lib
)

target_link_libraries(helloworld_test 
    ${Boost_LIBRARIES} 
    helloworld_lib
)




install(TARGETS helloworld_cli RUNTIME DESTINATION bin COMPONENT helloworld)


set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT ranihilaltor@gmail.com)

include (CPack)

enable_testing()

add_test(
  NAME boost_test
  COMMAND helloworld_test
)
