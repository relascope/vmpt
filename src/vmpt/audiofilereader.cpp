#include "audiofilereader.h"

#include <QDebug>
#include <QFile>
#include <QFileInfo>

#include <sndfile.hh>

#include <string.h>

AudioFileReader::AudioFileReader(QString audioFile) :
    m_fileName(audioFile)
  , m_sndfile(audioFile.toStdString())
  , m_file(0)
{
    if (!fileExists(audioFile))
        throw "File not found ";
}

bool AudioFileReader::fileExists(QString path) {
    QFileInfo checkFile(path);
    // check if file exists and if yes: Is it really a file and no directory?
    if (checkFile.exists() && checkFile.isFile()) {
        return true;
    } else {
        return false;
    }
}

int AudioFileReader::readRawFloat(float *buffer, int size)
{
    char* charbuff = new char[size * sizeof(float)];
    qint64 readCount = m_file->read(charbuff, size * sizeof(float));

    memcpy(buffer, charbuff, readCount);

    return readCount / sizeof(float);
}

int AudioFileReader::ReadFloat(float* buffer, int size)
{
    if (!m_file)
        return m_sndfile.readf(buffer, size);
    else
        return readRawFloat(buffer, size);
}

AudioFileReader::AUDIO_FILE_INFO AudioFileReader::opensnd()
{
    AUDIO_FILE_INFO result;

    if (!m_sndfile.error()) {
        result.channels = m_sndfile.channels();
        result.samplerate = m_sndfile.samplerate();
    } else {
        QString msg("Error loading file: ");
        msg += m_sndfile.strError();

        qDebug() << msg;
        qDebug() << "We try to read raw data... ";

        // begin to work...
        // we try to provide a fake info in the format of the recording we support
        result.channels = 1;
        result.samplerate = 44100;

        m_file = new QFile(m_fileName);
        m_file->open(QIODevice::ReadOnly);
    }

    return result;
}

AudioFileReader::~AudioFileReader()
{
    if (m_file)
    {
        if (m_file->isOpen())
            m_file->close();
        delete m_file;
    }
}
