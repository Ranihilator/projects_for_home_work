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

project(simple_uml VERSION ${VERSION_BUILD_MAJOR}.${VERSION_BUILD_MINOR}.${VERSION_BUILD})

set(HEADER_VERSION_PATH "${PROJECT_SOURCE_DIR}/../hw_01")

set(HEADER_PATH "${PROJECT_SOURCE_DIR}/include")
set(SOURCE_PATH "${PROJECT_SOURCE_DIR}/src")

set(HEADER_FILES
    ${SOURCE_PATH}/editor.h 
    ${SOURCE_PATH}/docs/docs.h 
    ${SOURCE_PATH}/docs/canvas/canvas.h 
    ${SOURCE_PATH}/docs/canvas/shapes/elements/ishape.h 
    ${SOURCE_PATH}/docs/canvas/shapes/elements/points.h 
    ${SOURCE_PATH}/docs/canvas/shapes/elements/lines.h 
    ${SOURCE_PATH}/docs/canvas/shapes/elements/polygons.h 
    ${SOURCE_PATH}/docs/canvas/shapes/elements/circles.h 
    ${SOURCE_PATH}/docs/canvas/shapes/shapes.h 
    ${SOURCE_PATH}/docs/canvas/data/file.h 
    ${SOURCE_PATH}/docs/canvas/data/format/cdr.h
    ${SOURCE_PATH}/docs/canvas/data/format/dxf.h
    ${SOURCE_PATH}/docs/canvas/data/format/iformat.h
    ${SOURCE_PATH}/docs/canvas/data/format/svg.h
    ${SOURCE_PATH}/docs/canvas/data/format/vsd.h
)

set(SOURCE_FILES 
    ${SOURCE_PATH}/editor.cpp 
    ${SOURCE_PATH}/docs/docs.cpp 
    ${SOURCE_PATH}/docs/canvas/canvas.cpp 
    ${SOURCE_PATH}/docs/canvas/shapes/elements/points.cpp
    ${SOURCE_PATH}/docs/canvas/shapes/elements/lines.cpp
    ${SOURCE_PATH}/docs/canvas/shapes/elements/polygons.cpp 
    ${SOURCE_PATH}/docs/canvas/shapes/elements/circles.cpp
    ${SOURCE_PATH}/docs/canvas/shapes/shapes.cpp
    ${SOURCE_PATH}/docs/canvas/data/file.cpp 
    ${SOURCE_PATH}/docs/canvas/data/format/cdr.cpp
    ${SOURCE_PATH}/docs/canvas/data/format/dxf.cpp
    ${SOURCE_PATH}/docs/canvas/data/format/svg.cpp
    ${SOURCE_PATH}/docs/canvas/data/format/vsd.cpp
)

add_executable(simple_uml ${SOURCE_PATH}/main.cpp ${HEADER_FILES} ${SOURCE_FILES})
add_library(version_lib STATIC IMPORTED)

set_property(TARGET version_lib PROPERTY IMPORTED_LOCATION ${HEADER_VERSION_PATH}/build/libhelloworld_lib.a)
#set_property(TARGET version_lib PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/../build/hw_01/libhelloworld_lib.a)

target_include_directories(simple_uml PRIVATE ${HEADER_PATH} ${HEADER_VERSION_PATH}/include ${SOURCE_PATH}/docs/canvas/shapes)

set_target_properties(simple_uml version_lib PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

target_link_libraries(simple_uml version_lib
)

install(TARGETS simple_uml RUNTIME DESTINATION bin COMPONENT simple_uml)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT ranihilaltor@gmail.com)

include (CPack)
set(CPACK_DEB_COMPONENT_INSTALL 1)