#ifndef RAWFILEAUDIOREADER_H
#define RAWFILEAUDIOREADER_H

#include <memory>

#include <QFile>
#include <QString>

#include "iaudioreader.h"

class RawFileAudioReader : public IAudioReader {
public:
    static bool mayReadFile(QString fileName);
    static std::unique_ptr<RawFileAudioReader> create(QString fileName);

    // IAudioReader interface
public:
    int readFloat(float *buffer, int size);
    AUDIO_INFO getFileInfo();
private:
    RawFileAudioReader(QString fileName);
    QFile m_fileHandle;
};

#endif // RAWFILEAUDIOREADER_H
