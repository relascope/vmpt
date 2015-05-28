INCLUDEPATH  += $$PWD

CONFIG += c++11

LIBS += -lvamp-hostsdk
LIBS += -lmusicxml2
LIBS += -lsndfile


SOURCES += \
    $$PWD/realtimevamphost.cpp \
    $$PWD/mxmlwriter.cpp \
    $$PWD/filetoscore.cpp \
    $$PWD/transcribehelper.cpp \
    $$PWD/debughelper.cpp \
    $$PWD/sndfileaudioreader.cpp \
    $$PWD/rawfileaudioreader.cpp \
    $$PWD/audioreaderfactory.cpp

HEADERS += \
    $$PWD/realtimevamphost.h \
    $$PWD/debughelper.h \
    $$PWD/mxmlwriter.h \
    $$PWD/filetoscore.h \
    $$PWD/transcribehelper.h \
    $$PWD/iaudioreader.h \
    $$PWD/sndfileaudioreader.h \
    $$PWD/rawfileaudioreader.h \
    $$PWD/audioreaderfactory.h
