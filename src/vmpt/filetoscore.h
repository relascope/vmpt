#ifndef FILETOSCORE_H
#define FILETOSCORE_H

#include <mxmlwriter.h>

#include <vamp-hostsdk/RealTime.h>
#include <vamp-hostsdk/Plugin.h>

using Vamp::Plugin;

class SoundFile
{
public:
    SoundFile(QString soundFileInput);
    virtual ~SoundFile();

    void toMusicXML(QString mxmlFileOutput);

private:
    void collectFeatures(Plugin::FeatureList *features);
    void writeNoteToScore(float val, Vamp::RealTime duration, Vamp::RealTime timestamp);

private:
    QString m_soundFileInput;
    MXMLWriter *m_outputxml;
};

#endif // FILETOSCORE_H
