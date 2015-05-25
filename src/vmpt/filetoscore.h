#ifndef FILETOSCORE_H
#define FILETOSCORE_H

#include <sndfile.h>
#include <mxmlwriter.h>

#include "realtimevamphost.h"

class FileToScore : ReadInterface
{
public:
    FileToScore();
    virtual ~FileToScore();

    void processSndFile(QString soundFileInput, QString mxmlFileOutput);

private:
    int readFloatSND(float *buffer, int size);

    void printFeatures(Plugin::FeatureList *features);

    void printNote(float val, Vamp::RealTime duration, Vamp::RealTime timestamp);

private:
    SNDFILE *m_sndfile;
    MXMLWriter *outputxml;

    // ReadInterface interface
public:
    int ReadFloat(float *buffer, int size) { readFloatSND(buffer, size); }
};

#endif // FILETOSCORE_H
