#include <QtTest/QtTest>

#include "transcribetest.h"
#include "audiofilereadertest.h"
#include "sndfiletest.h"
#include "sndfiletesthh.h"

#include "testrunner.h"


#include <QDebug>


QDir getAudioDir()
{
    QDir appDir = QCoreApplication::applicationDirPath();

    appDir.cdUp();
    appDir.cdUp();
    appDir.cd("audio");

    return appDir;
}



void Read(ReadFloatInterface &reader)
{
//     get some data (100k)
    int size = 100000 / sizeof(float);
    float *buffer = new float[size];
    int readSize = reader.ReadFloat(buffer, size);

}


void FIX()
{
    QString file = getAudioDir().absoluteFilePath("fini2.wav");

    AudioFileReader reader(file);

    AudioFileReader::AUDIO_FILE_INFO fileInfo = reader.opensnd();

    Read(reader);

//    QVERIFY2(fileInfo.channels == 2, "channel count mismatch");

    // get some data (100k)
//    int size = 100000 / sizeof(float);
//    float *buffer = new float[size];
//    int readSize = reader.ReadFloat(buffer, size);

//    QVERIFY2(readSize == size, "couldn't read audio file");
}

int main(int argc, char **argv) {

        QCoreApplication a(argc, argv);

    FIX();

//    TestRunner testRunner;

//    testRunner.addTest(new SndFileHHTest());

//    testRunner.addTest(new SndfileTest());

//    testRunner.addTest(new TranscribeTest());
//    testRunner.addTest(new AudioFileReaderTest());
//    qDebug() << "Overall result: " << (testRunner.runTests()?"====PASS====":"XXX - - - F A I L - - -XXX - - - WORK HARDER! www.dojoy.at needs YOU!");

    return a.exec();
}
