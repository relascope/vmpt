#include "rawfileaudioreader.h"

RawFileAudioReader::RawFileAudioReader(QString fileName)
    : m_fileHandle(fileName)
{
    m_fileHandle.open(QIODevice::ReadOnly); // gets closed in destructor
}

std::unique_ptr<RawFileAudioReader>
RawFileAudioReader::create(QString fileName) {
    return std::unique_ptr<RawFileAudioReader>(new RawFileAudioReader(fileName));
}

bool
RawFileAudioReader::mayReadFile(QString fileName)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);

    bool ret = file.exists() && file.isReadable();

    file.close();
    return ret;
}

// IAudioReader interface
int
RawFileAudioReader::readFloat(float *buffer, int size) {
    char* charbuff = new char[size * sizeof(float)];
    qint64 readCount = m_fileHandle.read(charbuff, size * sizeof(float));

    memcpy(buffer, charbuff, readCount);

    return readCount / sizeof(float);
}

IAudioReader::AUDIO_INFO
RawFileAudioReader::getFileInfo()
{
    AUDIO_INFO result;
    memset(&result, 0, sizeof(AUDIO_INFO));

    // TODO DoJoY HACK where do we get values, when reading raw?
    result.channels = 1;
    result.samplerate = 41000;

    return result;
}
