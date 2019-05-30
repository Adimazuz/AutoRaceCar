TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    IUDPServer.cpp \
    UDPServer.cpp

HEADERS += \
    Exceptions.h \
    IUDPServer.h \
    UDPServer.h \
    UDPServer_types.h
