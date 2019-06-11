cmake_minimum_required(VERSION 2.8)

project(Serial)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
    Serial.h
    Serial.cpp
    ISerial.h
    ISerial.cpp
    Serial_types.h)

#add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_library(serial SHARED
    Serial.h
    Serial.cpp
    ISerial.h
    ISerial.cpp
    Serial_types.h)
