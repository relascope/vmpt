#ifndef FILETOSCORE_H
#define FILETOSCORE_H

#include <vamp-hostsdk/RealTime.h>
#include <vamp-hostsdk/Plugin.h>
#include "mxmlwriter.h"

using Vamp::Plugin;
using std::string;

// TODO DoJoY Better description
class GenerateScore
{
private:
    // TODO DoJoY will be refactored to better reading...
    GenerateScore(string soundFileInput);
public:
    GenerateScore();
    virtual ~GenerateScore();

    GenerateScore& fromAudioFile(string soundFileInput);

    void toMusicXML(string mxmlFileOutput);

private:
    void collectFeatures(Plugin::FeatureList *features);
    void writeNoteToScore(float val, Vamp::RealTime duration, Vamp::RealTime timestamp);

    void fileToScore(string mxmlFileOutput);

    void microphoneToScore(string mxmlFileOutput);

private:
    typedef enum
    {
        UNDEFINED = -1,
        LOCAL_FILE,
        MICROPHONE,
    } InputType;
private:
    string m_soundFileInput;
    MXMLWriter *m_outputxml;

    InputType m_inputType;
};

#endif // FILETOSCORE_H
