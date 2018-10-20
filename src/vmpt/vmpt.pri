INCLUDEPATH  += $$PWD

CONFIG += c++11

LIBS += -lvamp-hostsdk
LIBS += -lsndfile


SOURCES += \
    $$PWD/realtimevamphost.cpp \
    $$PWD/transcribehelper.cpp \
    $$PWD/sndfileaudioreader.cpp \
    $$PWD/audioreaderfactory.cpp \
    $$PWD/generatescore.cpp

HEADERS += \
    $$PWD/realtimevamphost.h \
    $$PWD/transcribehelper.h \
    $$PWD/iaudioreader.h \
    $$PWD/sndfileaudioreader.h \
    $$PWD/audioreaderfactory.h \
    $$PWD/generatescore.h
