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

project(allocator VERSION ${VERSION_BUILD_MAJOR}.${VERSION_BUILD_MINOR}.${VERSION_BUILD})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

set(HEADER_PATH "${PROJECT_SOURCE_DIR}/include")
set(SOURCE_PATH "${PROJECT_SOURCE_DIR}/src")
set(TEST_PATH "${PROJECT_SOURCE_DIR}/test")

set(HEADER_FILES ${HEADER_PATH}/allocator.h ${HEADER_PATH}/container.h ${HEADER_PATH}/memory_rebind.h)

add_executable(allocator ${SOURCE_PATH}/main.cpp ${HEADER_FILES})
add_executable(allocator_testing ${TEST_PATH}/test_allocator.cpp  ${HEADER_FILES})
add_executable(container_testing ${TEST_PATH}/test_container.cpp  ${HEADER_FILES})

target_include_directories(allocator PRIVATE ${HEADER_PATH})

set_target_properties(allocator allocator_testing container_testing PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

set_target_properties(allocator_testing container_testing PROPERTIES
  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
  INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
  INCLUDE_DIRECTORIES ${HEADER_PATH}
)

target_link_libraries(allocator 
    
)

target_link_libraries(allocator_testing
    ${Boost_LIBRARIES} 
    
)

target_link_libraries(container_testing
    ${Boost_LIBRARIES} 
    
)

install(TARGETS allocator RUNTIME DESTINATION bin COMPONENT allocator)

set(CPACK_GENERATOR DEB)


set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT ranihilaltor@gmail.com)

include (CPack)
set(CPACK_DEB_COMPONENT_INSTALL 1)

enable_testing()

add_test(
  NAME boost_test_allocator
  COMMAND allocator_testing
)

add_test(
  NAME boost_test_container
  COMMAND container_testing
)

