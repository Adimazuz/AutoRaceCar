cmake_minimum_required(VERSION 2.8)

project(PubSub)

set(SOURCE_FILES
    main.cpp
    PubSub.cpp
    PubSub.h
    Subscriber.cpp
    Subscriber.h
    Data.cpp
    Data.h
    Publisher.cpp
    Publisher.h
    Semaphore.cpp
    Semaphore.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
