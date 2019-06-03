cmake_minimum_required(VERSION 3.12)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        raceCar.h
        raceCar.cpp
        MotorController.cpp
        MotorController.hpp)

add_executable(${SOURCE_FILES})