#ifndef AUDIOFILEREADERTEST_H
#define AUDIOFILEREADERTEST_H

#include <QtTest/QtTest>
#include <QObject>

#include "testrunner.h"
#include "testhelper.h"

#include "sndfileaudioreader.h"
#include "rawfileaudioreader.h"

class AudioFileReaderTest : public QObject
{
    Q_OBJECT
private slots:
    void testConstruction() {

        auto readerS1 = SndFileAudioReader::create(getOneChannelFileName());
        auto readerS2 = SndFileAudioReader::create(getTwoChannelFileName());

        auto readerR1 = RawFileAudioReader::create(getOneChannelFileName());
        auto readerR2 = RawFileAudioReader::create(getTwoChannelFileName());
    }

    void readOneChannelFile() {
        std::unique_ptr<IAudioReader> reader = SndFileAudioReader::create(getOneChannelFileName());
        IAudioReader::AUDIO_INFO audioInfo = reader->getFileInfo();

        QCOMPARE(audioInfo.channels, 1);

        int size = 1024;
        float *buffer = new float[size];
        int readSize = reader->readFloat(buffer, size);

        QVERIFY2(readSize > 0, "Could not read from file");

        delete [] buffer;
    }

    void readTwoChannelFile() {
        std::unique_ptr<IAudioReader> reader = SndFileAudioReader::create(getTwoChannelFileName());
        IAudioReader::AUDIO_INFO audioInfo = reader->getFileInfo();

        QCOMPARE(audioInfo.channels, 2);

        int size = 1024;
        float *buffer = new float[size];
        int readSize = reader->readFloat(buffer, size);

        QVERIFY2(readSize > 0, "Could not read from file");

//        delete [] buffer;
    }

    void readTwoChannelFileCapsulated() {
        int size = 1024;
        float *buffer = new float[size];

        {
            std::unique_ptr<IAudioReader> reader = SndFileAudioReader::create(getTwoChannelFileName());
        IAudioReader::AUDIO_INFO audioInfo = reader->getFileInfo();

        QCOMPARE(audioInfo.channels, 2);

        int readSize = reader->readFloat(buffer, size);

        QVERIFY2(readSize > 0, "Could not read from file");
        }

        delete [] buffer;
    }
};

//DECLARE_TEST(AudioFileReaderTest)

#endif // AUDIOFILEREADERTEST_H
