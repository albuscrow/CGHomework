cmake_minimum_required(VERSION 2.8)
project(cg)

list(APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")

FILE(GLOB HEADER_FILES ${PROJECT_SOURCE_DIR}/include/*.h)
source_group(Include FILES ${HEADER_FILES})

add_subdirectory(src)
add_subdirectory(tinyobjloader)
