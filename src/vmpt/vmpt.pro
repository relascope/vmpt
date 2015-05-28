#-------------------------------------------------
#
# Project created by QtCreator 2015-05-22T15:00:01
#
#-------------------------------------------------

QT  += core
QT  -= gui
QT  += multimedia

TARGET = vmpt
CONFIG   += console
CONFIG   -= app_bundle

CONFIG += c++11

TEMPLATE = app


#LIBS += -lvamp-hostsdk
#LIBS += -lmusicxml2
#LIBS += -lsndfile


SOURCES += main.cpp \

include(vmpt.pri)
