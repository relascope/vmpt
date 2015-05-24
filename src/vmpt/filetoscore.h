#ifndef FILETOSCORE_H
#define FILETOSCORE_H

#include <sndfile.h>
#include <mxmlwriter.h>

#include "realtimevamphost.h"

class FileToScore
{
public:
    FileToScore();
    virtual ~FileToScore();

    void processSndFile(QString soundFileInput, QString mxmlFileOutput);

private:
    int64_t readFloatSND(float *buffer, int64_t size);

    static int64_t readFloatForwarder(void* context, float *buffer, int64_t size) {
        return static_cast<FileToScore*>(context)->readFloatSND(buffer, size);
    }

    void printFeatures(Plugin::FeatureList *features);

    void printNote(float val);

private:
    SNDFILE *sndfile;
    MXMLWriter *outputxml;
};

#endif // FILETOSCORE_H
