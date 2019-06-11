cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)
project(cameraAPI)

add_executable(${PROJECT_NAME} "main.cpp" "RealSenseAPI.h" "RealSenseAPI.cpp" "api_how_to.h" "Image.h" "Exceptions.h")
target_link_libraries(${PROJECT_NAME} -lrealsense2)
