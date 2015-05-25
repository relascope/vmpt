#-------------------------------------------------
#
# Project created by QtCreator 2015-05-22T15:00:01
#
#-------------------------------------------------

QT       += core

QT       -= gui

# comment if ccache is not installed
QMAKE_CXX = ccache g++

TARGET = vmpt
CONFIG   += console
CONFIG   -= app_bundle

CONFIG += c++11

TEMPLATE = app


LIBS += -lvamp-hostsdk

LIBS += -lmusicxml2

LIBS += -lsndfile

SOURCES += main.cpp \
    realtimevamphost.cpp \
    mxmlwriter.cpp \
    filetoscore.cpp \
    transcribehelper.cpp \
    debughelper.cpp \
    audiofilereader.cpp

HEADERS += \
    realtimevamphost.h \
    debughelper.h \
    mxmlwriter.h \
    filetoscore.h \
    transcribehelper.h \
    audiofilereader.h \
    readfloatinterface.h
