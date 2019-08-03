cmake_minimum_required(VERSION 2.8)

project(Chaos)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")

set(SOURCE_FILES
    main.cpp
    RaceCar.cpp
    RaceCar.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../TcpClient/ITcpClient.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../motorAPI/Arduino.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../motorAPI/Arduino.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../motorAPI/MotorController.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../Serial/ISerial.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../motorAPI/MotorController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../cameraAPI/RealSenseAPI.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../cameraAPI/RealSenseAPI.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../cameraAPI/Exceptions.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../TcpServer/ITcpServer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../cameraAPI/Camera_types.h
    )




set(INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/../TcpClient
        ${CMAKE_CURRENT_SOURCE_DIR}/../TcpClientarduino/RaceCarArd
    ${CMAKE_CURRENT_SOURCE_DIR}/../TcpServer
    ${CMAKE_CURRENT_SOURCE_DIR}/../motorAPI
    ${CMAKE_CURRENT_SOURCE_DIR}/../arduino/RaceCarArd
    ${CMAKE_CURRENT_SOURCE_DIR}/../cameraAPI
    ${CMAKE_CURRENT_SOURCE_DIR}/../Serial
    )


INCLUDE_DIRECTORIES(${INCLUDES})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/bin/libTcpClient.so
    ${CMAKE_CURRENT_SOURCE_DIR}/bin/libserial.so
    ${CMAKE_CURRENT_SOURCE_DIR}/bin/libTcpServer.so
    -lrealsense2
    -lz)



