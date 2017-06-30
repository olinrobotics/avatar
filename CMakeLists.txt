cmake_minimum_required(VERSION 3.7)
project(avatar)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        get_features.cpp
        README.md)

add_executable(avatar ${SOURCE_FILES})

find_package(dlib REQUIRED)
include_directories(${dlib INCLUDE DIRS})
set(LIBS ${LIBS} ${dlib_LIBRARIES})

# 'ship' the dlib library within the project
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")


target_link_libraries(${PROJECT_NAME} ${dlib_LIBS})