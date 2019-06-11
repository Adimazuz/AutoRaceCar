cmake_minimum_required(VERSION 3.5)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        Arduino.h
        Arduino.cpp
        MotorController.cpp
        MotorController.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../Serial/ISerial.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../Serial/ISerial.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Serial/Serial.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Serial/Serial.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../Serial/Serial_types.h)

set(INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/../Serial)

INCLUDE_DIRECTORIES(${INCLUDES})

add_executable(${SOURCE_FILES})
