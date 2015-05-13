include_directories(${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/tinyobjloader )


# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)
file(GLOB_RECURSE SRC_FILES *.cpp)

# Tell CMake to create the helloworld executable
add_executable(cz ${SRC_FILES} ../include/ScanLineZBuffer.h ../include/MainWidget.h)

# Use the Widgets module from Qt 5.
target_link_libraries(cz Qt5::Widgets tinyobjloader obj)

#add_definitions(-std=c++11)
#file(GLOB_RECURSE SRC_FILES *.cpp)
#add_executable(euler_opt ${SRC_FILES})
#target_link_libraries(euler_opt boost_system GL GLU glut)
