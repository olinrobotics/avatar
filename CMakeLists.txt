cmake_minimum_required(VERSION 3.7)
project(avatar)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        control_avatar.cpp)

add_executable(avatar ${SOURCE_FILES})

# Link dlib
find_package(dlib REQUIRED)
include_directories(${DLIB_INCLUDE_DIRS})
set(LIBS ${LIBS} ${dlib_LIBRARIES})

# 'ship' the dlib library within the project
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

target_link_libraries(${PROJECT_NAME} ${dlib_LIBS})

# Link openCV
set(OpenCV_DIR "/usr/lib/opencv")
find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui)
include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

