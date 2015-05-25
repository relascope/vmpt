#ifndef AUDIOFILEREADER_H
#define AUDIOFILEREADER_H

#include <string>

#include <sndfile.h>

#include "readfloatinterface.h"

using std::string;

class AudioFileReader : public ReadFloatInterface
{
public:
    AudioFileReader(string audioFile);
    virtual ~AudioFileReader();

    SF_INFO opensnd();

    int ReadFloat(float *buffer, int size);

private:
    string m_fileName;
    SNDFILE *m_sndfiletmp;
    SF_INFO m_fileInfo;
};

#endif // AUDIOFILEREADER_H
