#ifndef AUDIOFILEREADERTEST_H
#define AUDIOFILEREADERTEST_H

#include <QtTest/QtTest>
#include <QObject>


#include <QCoreApplication>
#include <QDir>



//class AudioFileReaderTest : public QObject
//{
//    Q_OBJECT
//private slots:

//    void testDestructor() {
//        AudioFileReader reader(""), *preader;

//        preader = new AudioFileReader("");

//        delete preader;
//    }

//    void testWavTwoChannels() {
//        QString file = getAudioDir().absoluteFilePath("fini2.wav");

//        AudioFileReader reader(file);

//        AudioFileReader::AUDIO_FILE_INFO fileInfo = reader.opensnd();

//        QVERIFY2(fileInfo.channels == 2, "channel count mismatch");

//        // get some data (100k)
//        int size = 100000 / sizeof(float);
//        float *buffer = new float[size];
//        int readSize = reader.ReadFloat(buffer, size);

//        QVERIFY2(readSize == size, "couldn't read audio file");

////        delete[] buffer;

//    }

//    void testWavOneChannel() {
//        QString file = getAudioDir().absoluteFilePath("fini1.wav");

//        AudioFileReader reader(file);

//        AudioFileReader::AUDIO_FILE_INFO fileInfo = reader.opensnd();

//        QVERIFY2(fileInfo.channels == 1, "channel count mismatch");

//        // get some data (100k)
//        int size = 100000 / sizeof(float);
//        float *buffer = new float[size];
//        int readSize = reader.ReadFloat(buffer, size);

//        QVERIFY2(readSize == size, "couldn't read audio file");

//        delete[] buffer;
//    }


//    void testRawOneChannel() {
////        QVERIFY2(false, "NOT IMPLEMENTED");
//    }
//private:
//    void testAudioFile(QString file, int expectedChannels) {
////        AudioFileReader reader(file);

////        AudioFileReader::AUDIO_FILE_INFO fileInfo = reader.opensnd();

////        QVERIFY2(fileInfo.channels == expectedChannels, "channel count mismatch");


//        AudioFileReader *preader = new AudioFileReader(file);
//        preader->opensnd();

//        float* filebuf = new float[1014 * expectedChannels];
//        preader->ReadFloat(filebuf, 1024);

////        delete [] filebuf;

//        delete preader;

////        float* filebuf = new float[1014 * expectedChannels];
////        reader.ReadFloat(filebuf, 1024);


////        // get some data (10k)
////        int size = 10000 / sizeof(float);
////        float *buffer = new float[size];
//////        float buffer[size];
////        int readSize = reader.ReadFloat(buffer, size);

////        QVERIFY2(readSize == size, "couldn't read audio file");

//////        while (reader.ReadFloat(buffer, 1024));

//////        delete [] buffer;

//    }

//protected:

//    QDir getAudioDir()
//    {
//        QDir appDir = QCoreApplication::applicationDirPath();

//        appDir.cdUp();
//        appDir.cdUp();
//        appDir.cd("audio");

//        return appDir;
//    }
//};

#endif // AUDIOFILEREADERTEST_H
