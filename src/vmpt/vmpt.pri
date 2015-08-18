INCLUDEPATH  += $$PWD

CONFIG += c++11

LIBS += -lvamp-hostsdk
LIBS += -lmusicxml2
LIBS += -lsndfile


SOURCES += \
    $$PWD/realtimevamphost.cpp \
    $$PWD/mxmlwriter.cpp \
    $$PWD/transcribehelper.cpp \
    $$PWD/sndfileaudioreader.cpp \
    $$PWD/audioreaderfactory.cpp \
    $$PWD/generatescore.cpp

HEADERS += \
    $$PWD/realtimevamphost.h \
    $$PWD/mxmlwriter.h \
    $$PWD/transcribehelper.h \
    $$PWD/iaudioreader.h \
    $$PWD/sndfileaudioreader.h \
    $$PWD/audioreaderfactory.h \
    $$PWD/generatescore.h
