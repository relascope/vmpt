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

TARGET = testproject
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../src/vmpt/


SOURCES += \
    main.cpp

HEADERS += \
    transcribetest.h \
    audiofilereadertest.h \
    testrunner.h \
    sndfiletest.h \
    sndfiletesthh.h \
    sndfileallinclusive.h


# TODOJOY copy paste from vmpt without main.pp

LIBS += -lvamp-hostsdk
LIBS += -lmusicxml2
LIBS += -lsndfile

SOURCES += \
    ../../src/vmpt/realtimevamphost.cpp \
    ../../src/vmpt/mxmlwriter.cpp \
    ../../src/vmpt/filetoscore.cpp \
    ../../src/vmpt/transcribehelper.cpp \
    ../../src/vmpt/debughelper.cpp \
    ../../src/vmpt/audiofilereader.cpp

HEADERS += \
    ../../src/vmpt/realtimevamphost.h \
    ../../src/vmpt/debughelper.h \
    ../../src/vmpt/mxmlwriter.h \
    ../../src/vmpt/filetoscore.h \
    ../../src/vmpt/transcribehelper.h \
    ../../src/vmpt/audiofilereader.h \
    ../../src/vmpt/readfloatinterface.h
