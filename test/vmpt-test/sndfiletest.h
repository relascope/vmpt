#ifndef SNDFILETEST_H
#define SNDFILETEST_H

#include <QtTest/QtTest>

#include <QDebug>

#include <sndfile.hh>


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
    void testOpenClose(){
        QString file("/home/dojoy/vmpt/audio/fini.wav");

//        sndfile = new SndfileHandle();
//        sndfile->

        SndfileHandle handle(file.toStdString());
                    float* buffer = new float[1024];

                    buffer = new float[1024];

                    handle.readf(buffer, 1024);


//        SF_INFO sfinfo;
//        memset(&sfinfo, 0, sizeof(sfinfo));

//        sndfile = sf_open(file.toStdString().c_str(), SFM_READ, &sfinfo);

//        if (sndfile)
//        {
//            float* buffer = new float[1024];

//            sf_readf_float(sndfile, buffer, 1024);


//            delete[] buffer;

//            sf_close(sndfile);
//        } else {
//            int len = 2048;
//            char* buff = new char[len];
//            sf_error_str(sndfile, buff, len);

//            QString msg("Error loading file: ");
//            msg += buff;

//            qDebug() << msg << buff;

//            QFAIL(msg.toStdString().c_str());
//        }

    }
public:
    SndfileHandle* sndfile = 0;

    virtual  ~SndfileTest() {
        if (sndfile)
            delete sndfile;
    }
};


#endif // SNDFILETEST_H

