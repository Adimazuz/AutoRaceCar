cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)
project(cameraAPI)

set(SOURCE_FILES
    main.cpp
    RealSenseAPI.h
    RealSenseAPI.cpp
    api_how_to.h
    Image.h
    Camera_types.h
    Exceptions.h
    )


INCLUDE_DIRECTORIES(${INCLUDES})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} -lrealsense2)
