#ifndef SNDFILEAUDIOREADER_H
#define SNDFILEAUDIOREADER_H

#include <sndfile.hh>

#include <memory>

#include <QString>

#include "iaudioreader.h"

class SndFileAudioReader : public IAudioReader {
public:
    static bool canReadFile(QString fileName);
    static std::unique_ptr<SndFileAudioReader> create(QString fileName);

    // IAudioReader interface
public:
    int readFloat(float *buffer, int size);
    AUDIO_INFO getFileInfo();
private:
    SndFileAudioReader(QString fileName);
    SndfileHandle m_fileHandle;
};

#endif // SNDFILEAUDIOREADER_H
