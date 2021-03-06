cmake_minimum_required(VERSION 2.8)

project(Chaos)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")

set(SOURCE_FILES
    main.cpp
    RaceCar.cpp
    RaceCar.h
    Chaos_types.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../TcpClient/TcpClient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../TcpClient/ITcpClient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../motorAPI/Arduino.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../motorAPI/MotorController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../cameraAPI/RealSenseAPI.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../TcpServer/ITcpServer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../TcpServer/TcpServer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../jpeg/JpegCompressor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Serial/Serial.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Serial/ISerial.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../bitcraze/bitcraze.cpp

    )


set(INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/../TcpClient
    ${CMAKE_CURRENT_SOURCE_DIR}/../TcpServer
    ${CMAKE_CURRENT_SOURCE_DIR}/../motorAPI
    ${CMAKE_CURRENT_SOURCE_DIR}/../arduino/bitcraze
    ${CMAKE_CURRENT_SOURCE_DIR}/../cameraAPI
    ${CMAKE_CURRENT_SOURCE_DIR}/../Serial
    ${CMAKE_CURRENT_SOURCE_DIR}/../jpeg
    ${CMAKE_CURRENT_SOURCE_DIR}/../bitcraze
    )


INCLUDE_DIRECTORIES(${INCLUDES})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
    -lrealsense2
    -lturbojpeg
    -lz)

#${CMAKE_CURRENT_SOURCE_DIR}/bin/libTcpClient.so
#${CMAKE_CURRENT_SOURCE_DIR}/bin/libserial.so
#${CMAKE_CURRENT_SOURCE_DIR}/bin/libTcpServer.so
#${CMAKE_CURRENT_SOURCE_DIR}/bin/libserial.so

