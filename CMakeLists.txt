cmake_minimum_required(VERSION 2.8)
project(Blind-Assistance)

#use dlib cmake file
include(../dlib/dlib/cmake)

#set flags for highest optimization
SET( CMAKE_CXX_FLAGS_DISTRIBUTION "-O3" )
SET( CMAKE_C_FLAGS_DISTRIBUTION "-O3" )
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
link_directories( "${CMAKE_BINARY_DIR}/res" )

#find opencv library
find_package( OpenCV REQUIRED )
add_executable( video_input.exe video_input.cpp )
target_link_libraries( video_input.exe ${OpenCV_LIBS} dlib )


