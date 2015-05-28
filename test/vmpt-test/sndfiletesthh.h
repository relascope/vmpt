#ifndef SNDFILETESTHH_H
#define SNDFILETESTHH_H

#include <QtTest/QtTest>

#include <sndfile.hh>

class SndFileHHTest :public QObject{
    Q_OBJECT

private slots:
    void testFail() {
          SndfileHandle handle("/home/dojoy/vmpt/audio/fini.wav");

          int read = 1024;

          float* buffer = new float[read];

          int readCount = handle.readf(buffer, read);

//          QCOMPARE(readCount, 1024);

//          QCOMPARE(readCount, read);

          QCOMPARE("H", "H");

          QCOMPARE(1, 1);


    }

    void testSucceed() {
    }
};

#endif // SNDFILETESTHH_H

