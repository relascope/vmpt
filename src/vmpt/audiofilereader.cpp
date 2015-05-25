#include "audiofilereader.h"

#include <string.h>

AudioFileReader::AudioFileReader(string audioFile) :
    m_fileName(audioFile)
{
}

int AudioFileReader::ReadFloat(float* buffer, int size)
{
    return sf_readf_float(m_sndfiletmp, buffer, size);
}

SF_INFO AudioFileReader::opensnd()
{
    memset(&m_fileInfo, 0, sizeof(SF_INFO));

    m_sndfiletmp = sf_open(m_fileName.c_str(), SFM_READ, &m_fileInfo);
    if (!m_sndfiletmp) {
        throw "Error loading file ";
    }

    return m_fileInfo;
}

AudioFileReader::~AudioFileReader()
{
    if (m_sndfiletmp)
        sf_close(m_sndfiletmp);
}
