#include "filetoscore.h"

#include "transcribehelper.h"

#include "debughelper.h"

FileToScore::FileToScore()
{

}

FileToScore::~FileToScore()
{

}

void FileToScore::processSndFile(QString soundFileInput, QString mxmlFileOutput)
{
    outputxml = new MXMLWriter(mxmlFileOutput.toStdString().c_str());

    SF_INFO sfinfo;
    memset(&sfinfo, 0, sizeof(SF_INFO));

    sndfile = sf_open(soundFileInput.toStdString().c_str(), SFM_READ, &sfinfo);
    if (!sndfile) {
        cerr << ": ERROR: Failed to open input file " << sf_strerror(sndfile) << endl;
        throw "Error loading file ";
    }

    auto fp = std::bind(&FileToScore::readFloatSND, this, _1, _2);

    RealTimeVampHost *myHost = new RealTimeVampHost("cepstral-pitchtracker",
                    "cepstral-pitchtracker", sfinfo.samplerate, sfinfo.channels, "notes", false,
        fp);

    auto fp2 = std::bind(&FileToScore::printFeatures, this, _1);
    myHost->featuresAvailable = fp2;

    myHost->process();

    outputxml->finish();

    delete outputxml;
    delete myHost;

}

int64_t FileToScore::readFloatSND(float *buffer, int64_t size)
{
    int64_t ret = sf_read_float(sndfile, buffer, size);

    DebugHelper::instance()->printFloatArray(buffer, ret);
    DebugHelper::instance()->printToFile("\r\n");

    return ret;
}

void FileToScore::printNote(float val)
{
    QString note = TranscribeHelper().getNoteFromFreq(val);

    outputxml->addNote(note, 4);
}

void FileToScore::printFeatures(Plugin::FeatureList *features)
{
    for (Plugin::Feature feature : *features)
    {
        for (float val : feature.values)
        {
            printNote(val);

            cout << val << " ";
        }
        if (features->size() > 0)
            cout << endl;
    }
}

