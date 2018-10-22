#-------------------------------------------------
#
# Project created by QtCreator 2015-05-26T02:15:27
#
#-------------------------------------------------

QT  += core
QT  -= gui
#QT  += multimedia
QT  +=  testlib

CONFIG += c++11
CONFIG += testcase

TARGET = vmpt-test
CONFIG   += console
CONFIG   -= app_bundle

QMAKE_CXXFLAGS += -pedantic
QMAKE_CXXFLAGS += -Wall
QMAKE_CXXFLAGS += -Wextra


TEMPLATE = app

INCLUDEPATH += ../../src/vmpt/


SOURCES += \
    main.cpp \
    testhelper.cpp

HEADERS += \
    transcribetest.h \
    testrunner.h \
    integrationreadonetwochannels.h \
    testhelper.h


include(../../src/vmpt/vmpt.pri)
