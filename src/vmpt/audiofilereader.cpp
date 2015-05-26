#include "audiofilereader.h"

#include <string.h>

#include <QDebug>

AudioFileReader::AudioFileReader(QString audioFile) :
    m_fileName(audioFile)
  , m_sndfiletmp(0)
  , m_file(0)
{
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
        return sf_readf_float(m_sndfiletmp, buffer, size);
    else if (!m_sndfiletmp)
        return readRawFloat(buffer, size);
    else
        throw "No File to read... ";
}

SF_INFO AudioFileReader::opensnd()
{
    memset(&m_fileInfo, 0, sizeof(SF_INFO));

    m_sndfiletmp = sf_open(m_fileName.toStdString().c_str(), SFM_READ, &m_fileInfo);
    if (!m_sndfiletmp) {
        int len = 2048;
        char* buff = new char[len];
        sf_error_str(m_sndfiletmp, buff, len);

        string msg("Error loading file: ");
        msg += buff;

        qDebug() << QString::fromStdString(msg);
        qDebug() << "We try to read raw data... ";

        // begin to work...
        // we try to provide a fake info in the format of the recording we support
        m_fileInfo.channels = 1;
        m_fileInfo.samplerate = 44100;

        m_file = new QFile(m_fileName);
        m_file->open(QIODevice::ReadOnly);
    }

    return m_fileInfo;
}

AudioFileReader::~AudioFileReader()
{
    if (m_sndfiletmp)
    {
        sf_close(m_sndfiletmp);
    }

    if (m_file)
    {
        if (m_file->isOpen())
            m_file->close();
        delete m_file;
    }
}
