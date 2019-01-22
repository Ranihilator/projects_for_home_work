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

project(home_work VERSION ${VERSION_BUILD_MAJOR}.${VERSION_BUILD_MINOR}.${VERSION_BUILD}) 

add_subdirectory(hw_01 hw_01)
add_subdirectory(hw_02 hw_02)
add_subdirectory(hw_03 hw_03)
add_subdirectory(hw_04 hw_04)
add_subdirectory(hw_05 hw_05)
add_subdirectory(hw_06 hw_06)
add_subdirectory(hw_07 hw_07)

set(CPACK_COMPONENTS_ALL helloworld ip_filter allocator print_ip simple_uml matrix bulk)

set(CPACK_GENERATOR DEB)
set(CPACK_DEB_COMPONENT_INSTALL ON)
SET(CPACK_SYSTEM_NAME "amd64")

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT ranihilaltor@gmail.com)

include (CPack)
