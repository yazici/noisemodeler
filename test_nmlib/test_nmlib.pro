TEMPLATE = app
TARGET = test_nmlib
QT -= gui core

QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    test_serialization.cpp

HEADERS +=

INCLUDEPATH = . ..

LIBS += -L../nmlib -lnmlib -lgtest -lgtest_main

