cmake_minimum_required(VERSION 3.2)

if($ENV{TRAVIS_BUILD_NUMBER})
    set(VERSION_BUILD $ENV{TRAVIS_BUILD_NUMBER})
else()
    set(VERSION_BUILD 1)
endif()

set(VERSION_BUILD_MAJOR 1)
set(VERSION_BUILD_MINOR 0)

project(simple_uml VERSION ${VERSION_BUILD_MAJOR}.${VERSION_BUILD_MINOR}.${VERSION_BUILD})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

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
    ${SOURCE_PATH}/docs/canvas/shapes/elements/star.h
    ${SOURCE_PATH}/docs/canvas/shapes/elements/pentagon.h
    ${SOURCE_PATH}/docs/canvas/shapes/shapes.h
    ${SOURCE_PATH}/docs/canvas/data/istore.h
    ${SOURCE_PATH}/docs/canvas/data/data_link.h
    ${SOURCE_PATH}/docs/canvas/data/file.h
    ${SOURCE_PATH}/docs/canvas/data/database.h
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
    ${SOURCE_PATH}/docs/canvas/shapes/elements/star.cpp
    ${SOURCE_PATH}/docs/canvas/shapes/elements/pentagon.cpp
    ${SOURCE_PATH}/docs/canvas/shapes/shapes.cpp
    ${SOURCE_PATH}/docs/canvas/data/data_link.cpp
    ${SOURCE_PATH}/docs/canvas/data/file.cpp
    ${SOURCE_PATH}/docs/canvas/data/database.cpp
    ${SOURCE_PATH}/docs/canvas/data/format/cdr.cpp
    ${SOURCE_PATH}/docs/canvas/data/format/dxf.cpp
    ${SOURCE_PATH}/docs/canvas/data/format/svg.cpp
    ${SOURCE_PATH}/docs/canvas/data/format/vsd.cpp
)

add_executable(simple_uml ${SOURCE_PATH}/main.cpp ${HEADER_FILES} ${SOURCE_FILES})
add_executable(simple_uml_test ${SOURCE_PATH}/test.cpp ${HEADER_FILES} ${SOURCE_FILES})

add_library(version_lib STATIC IMPORTED)

#set_property(TARGET version_lib PROPERTY IMPORTED_LOCATION ${HEADER_VERSION_PATH}/build/libhelloworld_lib.a)
set_property(TARGET version_lib PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/../build/hw_01/libhelloworld_lib.a)

set_target_properties(simple_uml version_lib PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  INCLUDE_DIRECTORIES "${HEADER_PATH};${HEADER_VERSION_PATH}/include;${SOURCE_PATH}/docs/canvas/shapes"
  LINK_LIBRARIES version_lib
)

set_target_properties(simple_uml_test PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  INCLUDE_DIRECTORIES "${Boost_INCLUDE_DIR};${HEADER_PATH};${HEADER_VERSION_PATH}/include;${SOURCE_PATH}/docs/canvas/shapes"
  LINK_LIBRARIES ${Boost_LIBRARIES} 
)

install(TARGETS simple_uml RUNTIME DESTINATION bin COMPONENT simple_uml)

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
  COMMAND simple_uml_test
)
