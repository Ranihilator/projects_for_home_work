cmake_minimum_required(VERSION 3.2)

project(home_work)

add_subdirectory(hw_01 hw_01)
add_subdirectory(hw_02 hw_02)
add_subdirectory(hw_03 hw_03)

set(CPACK_COMPONENTS_ALL helloworld ip_filter allocator)

set(CPACK_GENERATOR DEB)
set(CPACK_DEB_COMPONENT_INSTALL ON)

set(CPACK_PACKAGE_CONTACT ranihilaltor@gmail.com)

include (CPack)
