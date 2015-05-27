#ifndef AUDIOFILEREADER_H
#define AUDIOFILEREADER_H

#include <sndfile.hh>

#include <QString>

#include "readfloatinterface.h"

class QFile;

/**
 * @brief The AudioFileReader class
 * reads audio files supported by sndfile
 * and raw formats in the recording we use
 *   (no guessing - fixed values!!!)
 */
class AbstractAudioFileReader : public ReadFloatInterface
{
public:
    typedef struct {
        int channels;
        int samplerate;
    } AUDIO_FILE_INFO;

public:
    AbstractAudioFileReader(QString audioFile);
    virtual ~AbstractAudioFileReader();

    AUDIO_FILE_INFO opensnd();

    int ReadFloat(float *buffer, int size);
private:
    int readRawFloat(float *buffer, int size);
    bool fileExists(QString path);
private:
    QString m_fileName;
    SndfileHandle m_sndfile;
    QFile *m_file;
};

#endif // AUDIOFILEREADER_H
