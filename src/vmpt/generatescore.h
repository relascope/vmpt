#ifndef FILETOSCORE_H
#define FILETOSCORE_H

#include <vamp-hostsdk/RealTime.h>
#include <vamp-hostsdk/Plugin.h>

#include "mxmlwriter.h"

using Vamp::Plugin;

// TODO DoJoY Better description
class GenerateScore
{
private:
    // TODO DoJoY will be refactored to better reading...
    GenerateScore(QString soundFileInput);
public:
    GenerateScore();
    virtual ~GenerateScore();

    GenerateScore& fromAudioFile(QString soundFileInput);

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
