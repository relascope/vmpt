#ifndef AUDIOFILEREADER_H
#define AUDIOFILEREADER_H

#include <QString>
#include <QFile>

#include <sndfile.h>

#include "readfloatinterface.h"

using std::string;

/**
 * @brief The AudioFileReader class
 * reads audio files supported by sndfile
 * and raw formats in the recording we use
 *   (no guessing - fixed values!!!)
 */
class AudioFileReader : public ReadFloatInterface
{
public:
    AudioFileReader(QString audioFile);
    virtual ~AudioFileReader();

    SF_INFO opensnd();

    int ReadFloat(float *buffer, int size);
private:
    int readRawFloat(float *buffer, int size);
private:
    QString m_fileName;
    SNDFILE *m_sndfiletmp;
    SF_INFO m_fileInfo;
    QFile *m_file;
};

#endif // AUDIOFILEREADER_H
