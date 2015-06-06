#ifndef SNDFILETEST_H
#define SNDFILETEST_H

#include <sndfile.hh>

#include <QtTest/QtTest>
#include <QDebug>

#include "testrunner.h"
#include "testhelper.h"


/**
 * @brief The SndfileTest class
 * tests for libsndfile
 *
 * testing multiple closing of files...
 */
class SndfileTest : public QObject
{
    Q_OBJECT

private slots:

    void testSndFileHandleOpenRead() {
        QString file = getOneChannelFileName();

        SndfileHandle handle(file.toStdString());

        float* buffer = new float[1024];
        buffer = new float[1024];
        int bytesRead = handle.readf(buffer, 1024);

        QVERIFY2(bytesRead > 0, "Could not read bytes");
    }

    void testSndFileHandleMemberPointer() {
        QString file = getOneChannelFileName();

        m_sndfile = new SndfileHandle(file.toStdString());

        float* buffer = new float[1024];
        buffer = new float[1024];
        int bytesRead = m_sndfile->readf(buffer, 1024);

        QVERIFY2(bytesRead > 0, "Could not read bytes");

        delete m_sndfile;
        m_sndfile = 0;
    }

    void testSndFileHandleLocalPointer() {
        QString file = getOneChannelFileName();

        SndfileHandle *sndfile = new SndfileHandle(file.toStdString());

        float* buffer = new float[1024];
        buffer = new float[1024];
        int bytesRead = sndfile->readf(buffer, 1024);

        QVERIFY2(bytesRead > 0, "Could not read bytes");

        delete sndfile;
        sndfile = 0;
    }

    /// tests with 2channel file  !!! COPY/PASTE FROM ABOVE

    void testSndFileHandleOpenRead2() {
        QString file = getTwoChannelFileName();

        SndfileHandle handle(file.toStdString());

        float* buffer = new float[1024];
        buffer = new float[1024];
        int bytesRead = handle.readf(buffer, 1024);

        QVERIFY2(bytesRead > 0, "Could not read bytes");
    }

    void testSndFileHandleMemberPointer2() {
        QString file = getTwoChannelFileName();

        m_sndfile = new SndfileHandle(file.toStdString());

        float* buffer = new float[1024];
        buffer = new float[1024];
        int bytesRead = m_sndfile->readf(buffer, 1024);

        QVERIFY2(bytesRead > 0, "Could not read bytes");

        delete m_sndfile;
        m_sndfile = 0;
    }

    void testSndFileHandleLocalPointer2() {
        QString file = getTwoChannelFileName();

        SndfileHandle *sndfile = new SndfileHandle(file.toStdString());

        float* buffer = new float[1024];
        buffer = new float[1024];
        int bytesRead = sndfile->readf(buffer, 1024);

        QVERIFY2(bytesRead > 0, "Could not read bytes");

        delete sndfile;
        sndfile = 0;
    }


public:
    SndfileHandle* m_sndfile = 0;

    virtual  ~SndfileTest() {
        if (m_sndfile)
            delete m_sndfile;
    }
};

//DECLARE_TEST(SndfileTest)

#endif // SNDFILETEST_H

