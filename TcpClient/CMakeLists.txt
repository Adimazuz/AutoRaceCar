cmake_minimum_required(VERSION 3.5)
project(TcpClient)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        main.cpp
        ITcpClient.h
        TcpClient.h
        Exceptions.h
        ITcpClient.cpp
        TcpClient.cpp
        TcpClient_types.h)


add_executable(TcpClient ${SOURCE_FILES})

if(WIN32)
    target_link_libraries(TcpClient ws2_32)
endif(WIN32)
