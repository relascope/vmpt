#-------------------------------------------------
#
# Project created by QtCreator 2015-05-22T15:00:01
#
#-------------------------------------------------

#QMAKE_CXXFLAGS += -Werror


QT  += core
QT  -= gui
QT  += multimedia

TARGET = vmpt
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -lboost_program_options

SOURCES += main.cpp \

include(vmpt.pri)
