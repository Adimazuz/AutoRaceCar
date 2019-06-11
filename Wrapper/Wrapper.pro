TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    RaceCar.cpp \
    ../TcpClient/ITcpClient.cpp \
    ../TcpClient/TcpClient.cpp

HEADERS += \
    RaceCar.h \
    ../TcpClient/ITcpClient.h \
    ../motorAPI/MotorController.h

INCLUDEPATH += $$PWD/../TcpClient
