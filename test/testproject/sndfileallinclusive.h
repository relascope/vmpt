#ifndef SNDFILEALLINCLUSIVE_H
#define SNDFILEALLINCLUSIVE_H


/**
  * Everything worked fine until we started to implement the microphone input.
  * sndfile started to crash here and there on sf_close and so.
  * So we integrated QtTests.
  * We found out, the problem was NOT ther with one-channel wavs,
  * but crashed with TWO CHANNEL wavs.
  * Examining further, the same problem exists with the c++-wrapper (including sndfile.hh)
  *
  * The result is a mess of this testfiles.
  *
  * the tests are
  *  testgenericsndfileread();
  *  testsndfileread();
  *
  * where testsndfileread() uses an AudioReader only reading SNFILES
  * testgenericsndfileread() uses an AudioReader that falls back to raw wav reading
  *
  * each test run in an app succeeds...
  *   BUT
  *
  * run both of them (or one multiple times) and you get strange behaviour
  * sf_close crashes
  * Qt cannot initialise a string
  *
  * everything works fine for ONE CHANNEL WAVS
  * who is abusing some memory?
  *
  * Myself?
  * Chances are great since i am not a C++ programmer with long-time experience.
  *
  * STRANGE 1-channel succeeds, but not 2-channel
  *
  * so we decided to inform both...
  * Erik de Castro Lopo: Author of the great sndfile
  * Qt through contact form
  */


#include <sndfile.hh>

#include <QString>

using namespace std;

class xReadInterface
{
public:
    virtual int Read(float* buffer, int size) = 0;
};


#include <sndfile.hh>

#include <QString>


class QFile;

/**
 * @brief The AudioFileReader class
 * reads audio files supported by sndfile
 * and raw formats in the recording we use
 *   (no guessing - fixed values!!!)
 */
class xGenericAudioFileReader : public xReadInterface
{
public:
    typedef struct {
        int channels;
        int samplerate;
    } AUDIO_FILE_INFO;

public:
    xGenericAudioFileReader(QString audioFile);
    virtual ~xGenericAudioFileReader();

    AUDIO_FILE_INFO opensnd();

    int Read(float *buffer, int size);
private:
    int readRawFloat(float *buffer, int size);
    bool fileExists(QString path);
private:
    QString m_fileName;
    SndfileHandle m_sndfile;
    QFile *m_file;
};





#include "audiofilereader.h"

#include <QDebug>
#include <QFile>
#include <QFileInfo>

#include <sndfile.hh>

#include <string.h>







/////////////////////////////////////plain c++ no qt

#include <string>
#include <iostream>
#include <sndfile.hh>

using namespace std;

class xAudioFileReader : public xReadInterface
{
public:
    xAudioFileReader(string audioFile);
    virtual ~xAudioFileReader();

    void opensnd();

    int Read(float *buffer, int size);
private:
    SndfileHandle m_sndfile;
};


class xMyManager {
public:
    xMyManager(xReadInterface& rf) : reader(rf) {}
    xReadInterface& reader;

    int testRead() {
        //     get some data (10k)
            int size = 10000 / sizeof(float);
            float *buffer = new float[size];
            int readSize = reader.Read(buffer, size);

            return readSize;
    }
};


string getFileWithTwoChannels();

void Read(xReadInterface &reader);

void testsndfileread();

void testgenericsndfileread();

#endif // SNDFILEALLINCLUSIVE_H

