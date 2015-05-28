#include "sndfileaudioreader.h"

#include <QDebug>

SndFileAudioReader::SndFileAudioReader(QString fileName)
    : m_fileHandle(fileName.toStdString())
{
}

bool
SndFileAudioReader::canReadFile(QString fileName)
{
    SndfileHandle handle(fileName.toStdString());

    if (handle.error())
    {
        return false;
    }

    return true;
}

std::unique_ptr<SndFileAudioReader>
SndFileAudioReader::create(QString fileName)
{
    if (!canReadFile(fileName))
    {
        QString msg("SndFileReader cannot read file: ");
        msg += fileName;
        qCritical() << msg;
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
