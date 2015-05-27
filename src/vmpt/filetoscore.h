#ifndef FILETOSCORE_H
#define FILETOSCORE_H

#include <vamp-hostsdk/RealTime.h>
#include <vamp-hostsdk/Plugin.h>

#include "mxmlwriter.h"

using Vamp::Plugin;

// TODOJOY Better description
class SoundFile
{
public:
    SoundFile();
    SoundFile(QString soundFileInput);
    virtual ~SoundFile();

    SoundFile& fromFile(QString soundFileInput);
    SoundFile& fromMicrophone(qint64 recordingSeconds);

    void toMusicXML(QString mxmlFileOutput);

private:
    void collectFeatures(Plugin::FeatureList *features);
    void writeNoteToScore(float val, Vamp::RealTime duration, Vamp::RealTime timestamp);

    void fileToScore(QString mxmlFileOutput);

    void microphoneToScore(QString mxmlFileOutput);

private:
    typedef enum
    {
        UNDEFINED = -1,
        LOCAL_FILE,
        MICROPHONE,
    } InputType;
private:
    QString m_soundFileInput;
    MXMLWriter *m_outputxml;

    InputType m_inputType;
};

#endif // FILETOSCORE_H
