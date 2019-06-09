cmake_minimum_required(VERSION 2.8)

project(UdpServer)
set(SOURCE_FILES
    main.cpp
    IUdpServer.cpp
    IUdpServer.h
    UdpServer.cpp
    UdpServer.h
    UdpServer_types.h
    Exceptions.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

