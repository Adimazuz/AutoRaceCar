cmake_minimum_required(VERSION 3.10)
project(TcpServer)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES
        main.cpp
        ITcpServer.h
        ITcpServer.cpp
        TcpServer.h
        TcpServer.cpp
        Exceptions.h
        TcpSocket_types.h)

add_executable(TcpServer ${SOURCE_FILES})

if(WIN32)
    target_link_libraries(TcpServer ws2_32)
endif(WIN32)
