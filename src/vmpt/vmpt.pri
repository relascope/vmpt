
LIBS += -lvamp-hostsdk
LIBS += -lmusicxml2
LIBS += -lsndfile


SOURCES += \
    realtimevamphost.cpp \
    mxmlwriter.cpp \
    filetoscore.cpp \
    transcribehelper.cpp \
    debughelper.cpp \
    sndfileaudioreader.cpp \
    rawfileaudioreader.cpp \
    audioreaderfactory.cpp

HEADERS += \
    realtimevamphost.h \
    debughelper.h \
    mxmlwriter.h \
    filetoscore.h \
    transcribehelper.h \
    iaudioreader.h \
    sndfileaudioreader.h \
    rawfileaudioreader.h \
    audioreaderfactory.h
