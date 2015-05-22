#-------------------------------------------------
#
# Project created by QtCreator 2015-05-22T15:00:01
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = vmpt
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


LIBS += -lvamp-hostsdk

SOURCES += main.cpp \
    vamphost.cpp

HEADERS += \
    vamphost.h
