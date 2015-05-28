#-------------------------------------------------
#
# Project created by QtCreator 2015-05-26T02:15:27
#
#-------------------------------------------------

QT  += core
QT  -= gui
QT  += multimedia
QT  +=  testlib

CONFIG += c++11
CONFIG += testcase

TARGET = vmpt-test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../src/vmpt/


SOURCES += \
    main.cpp \
    sndfileallinclusive.cpp

HEADERS += \
    transcribetest.h \
    audiofilereadertest.h \
    testrunner.h \
    sndfiletest.h \
    sndfiletesthh.h \
    sndfileallinclusive.h


include(../../src/vmpt/vmpt.pri)
