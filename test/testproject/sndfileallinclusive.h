#ifndef SNDFILEALLINCLUSIVE_H
#define SNDFILEALLINCLUSIVE_H




#include <string>

using namespace std;


string getFileWithTwoChannels()
{
    return "/home/dojoy/vmpt/audio/fini2.wav";
}

#include <string>
#include <iostream>
#include <sndfile.hh>

using namespace std;

class ReadFloatInterface
{
public:
    virtual int ReadFloat(float* buffer, int size) = 0;
};

class AudioFileReader : public ReadFloatInterface
{
public:
    AudioFileReader(string audioFile);
    virtual ~AudioFileReader();

    void opensnd();

    int ReadFloat(float *buffer, int size);
private:
    SndfileHandle m_sndfile;
};


AudioFileReader::AudioFileReader(string audioFile)
  : m_sndfile(audioFile)
{
}

int AudioFileReader::ReadFloat(float* buffer, int size)
{
    return m_sndfile.readf(buffer, size);
}

void AudioFileReader::opensnd()
{

    if (!m_sndfile.error()) {
        // get fileinfo
    } else {
        // report error
        cerr << m_sndfile.strError() << endl;
        throw m_sndfile.strError();
    }
}

AudioFileReader::~AudioFileReader()
{
    // here once was if (m_sndfile) sf_close(); // but the same errors
}

class MyManager {
public:
    MyManager(ReadFloatInterface& rf) : reader(rf) {}
    ReadFloatInterface& reader;

    int testRead() {
        //     get some data (10k)
            int size = 10000 / sizeof(float);
            float *buffer = new float[size];
            int readSize = reader.ReadFloat(buffer, size);

            return readSize;
    }
};

void Read(ReadFloatInterface &reader)
{
//     get some data (10k)
    int size = 10000 / sizeof(float);
    float *buffer = new float[size];
    int readSize = reader.ReadFloat(buffer, size);

}

void testsndfileread()
{
    string file = getFileWithTwoChannels();

    AudioFileReader reader(file);

    reader.opensnd();

    MyManager man(reader);

    Read(reader);
    man.testRead();
}




#endif // SNDFILEALLINCLUSIVE_H

