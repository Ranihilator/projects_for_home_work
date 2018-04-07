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
find_package(spdlog REQUIRED)
find_package(Threads REQUIRED)
set(SOURCE_PATH "${PROJECT_SOURCE_DIR}/src")

configure_file(version.h.in ${SOURCE_PATH}/version.h)

add_executable(helloworld_cli ${SOURCE_PATH}/main.cpp)
add_executable(helloworld_test ${SOURCE_PATH}/test_main.cpp)

add_library(helloworld_lib ${SOURCE_PATH}/library.cpp)


set_target_properties(helloworld_cli helloworld_lib helloworld_test PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

set_target_properties(helloworld_test PROPERTIES
  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
  INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(helloworld_cli spdlog::spdlog Threads::Threads
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

add_test(test_version_valid helloworld_test)
