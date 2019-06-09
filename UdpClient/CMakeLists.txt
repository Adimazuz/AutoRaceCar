cmake_minimum_required(VERSION 2.8)

project(UdpClient)

set(SOURCE_FILES
    main.cpp
    IUdpClient.cpp
    IUdpClient.h
    UdpClient.cpp
    UdpClient.h
    UdpClient_types.h
    Exceptions.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
