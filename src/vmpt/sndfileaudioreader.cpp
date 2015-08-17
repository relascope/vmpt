#include "sndfileaudioreader.h"

#include <iostream>
#include <string.h>

SndFileAudioReader::SndFileAudioReader(std::string fileName)
    : m_fileHandle(fileName)
{
}

bool
SndFileAudioReader::canReadFile(std::string fileName)
{
    SndfileHandle handle(fileName);

    if (handle.error())
    {
        return false;
    }

    return true;
}

std::unique_ptr<SndFileAudioReader>
SndFileAudioReader::create(std::string fileName)
{
    if (!canReadFile(fileName))
    {
        std::string msg("SndFileReader cannot read file: ");
        msg += fileName;
        std::cerr << msg;
        throw msg;
    }

    return std::unique_ptr<SndFileAudioReader>(new SndFileAudioReader(fileName));
}

// IAudioReader interface
int
SndFileAudioReader::readFloat(float *buffer, int size) {
    return m_fileHandle.readf(buffer, size);
}

IAudioReader::AUDIO_INFO
SndFileAudioReader::getFileInfo()
{
    AUDIO_INFO result;
    memset(&result, 0, sizeof(AUDIO_INFO));

    result.channels = m_fileHandle.channels();
    result.samplerate = m_fileHandle.samplerate();

    return result;
}
