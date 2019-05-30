TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    IUDPClient.cpp \
    UDPClient.cpp

HEADERS += \
    Exceptions.h \
    IUDPClient.h \
    UDPClient.h \
    UDPClient_types.h
