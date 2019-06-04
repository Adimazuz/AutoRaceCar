cmake_minimum_required(VERSION 2.8)

project(Serial)

set(SOURCE_FILES
    main.cpp
    Serial.h
    Serial.cpp
    ISerial.h
    ISerial.cpp
    Serial_types.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
