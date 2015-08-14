#-------------------------------------------------
#
# Project created by QtCreator 2015-05-22T15:00:01
#
#-------------------------------------------------

QT  += core
QT  -= gui

TARGET = vmpt
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -lboost_program_options

#QMAKE_CXXFLAGS += -Werror
QMAKE_CXXFLAGS += -pedantic
QMAKE_CXXFLAGS += -Wall

#main kept here
SOURCES += main.cpp \

#split all other files to include, to be included
#in test project, e.g.
include(vmpt.pri)
