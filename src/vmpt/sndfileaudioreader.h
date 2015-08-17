#ifndef SNDFILEAUDIOREADER_H
#define SNDFILEAUDIOREADER_H

#include <sndfile.hh>
#include <memory>
#include "iaudioreader.h"

class SndFileAudioReader : public IAudioReader {
public:
    static bool canReadFile(std::string fileName);
    static std::unique_ptr<SndFileAudioReader> create(std::string fileName);

    // IAudioReader interface
public:
    int readFloat(float *buffer, int size);
    AUDIO_INFO getFileInfo();
private:
    SndFileAudioReader(std::string fileName);
    SndfileHandle m_fileHandle;
};

#endif // SNDFILEAUDIOREADER_H
