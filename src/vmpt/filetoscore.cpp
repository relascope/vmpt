#include "filetoscore.h"

#include "transcribehelper.h"

#include "debughelper.h"

FileToScore::FileToScore()
{

}

FileToScore::~FileToScore()
{
    if (m_sndfile)
        sf_close(m_sndfile);
}

void FileToScore::processSndFile(QString soundFileInput, QString mxmlFileOutput)
{
    outputxml = new MXMLWriter(mxmlFileOutput.toStdString().c_str());

    SF_INFO sfinfo;
    memset(&sfinfo, 0, sizeof(SF_INFO));

    m_sndfile = sf_open(soundFileInput.toStdString().c_str(), SFM_READ, &sfinfo);
    if (!m_sndfile) {
        cerr << ": ERROR: Failed to open input file " << sf_strerror(m_sndfile) << endl;
        throw "Error loading file ";
    }

    auto fp = std::bind(&FileToScore::readFloatSND, this, _1, _2);

    RealTimeVampHost *myHost = new RealTimeVampHost("cepstral-pitchtracker",
                    "cepstral-pitchtracker", sfinfo.samplerate, sfinfo.channels, "notes", false,
        fp);

    myHost->m_reader = this;

    auto fp2 = std::bind(&FileToScore::printFeatures, this, _1);
    myHost->featuresAvailable = fp2;


    myHost->process();

    outputxml->finish();

    delete outputxml;
    delete myHost;

}

int FileToScore::readFloatSND(float *buffer, int size)
{
    return sf_read_float(m_sndfile, buffer, size);
}

#define DIVISION_PER_QUARTER 16

void FileToScore::printNote(float val, RealTime duration, RealTime timestamp)
{
    float bpm = 130;

    /**
     * calc...
     * beats per minute given
     * duration in seconds given
     *
     * Which note?
     *
     * BPM = 60
     * duration = 1 sec
     * ==> quarter
     *
     * duration needed?
     * 4 is quarter
     * 2 is eigth
     *
     * BPM = 60
     * duration = 1 sec
     * ==> 4 (quarter)
     *
     * duration = 2 sec
     * ==> 8 (half)
     *
     * duration = 0.5 sec
     * ==> 2 (eigth)
     *
     *
     * BPM = 120
     * duration = 1 sec
     * ==> 8 (half)
     *
     * duration = 2 sec
     * ==> 16 (full)
     *
     * duration = 0.5 sec
     * ==> 4 (quarter)
     */

    // milli/micro/nano
    float fmxmlDuration = duration.nsec / (1000.f*1000.f*1000.f)  * DIVISION_PER_QUARTER * bpm / 60.f;

    int mxmlDuration = fmxmlDuration;

    // TODOJOY CHECK why?
//    if (mxmlDuration == 0)
//        return;

    // TODOJOY timestamp should be used to generate pause.... => last timestamp+duration needed...

    QString note = TranscribeHelper().getNoteFromFreq(val);

    outputxml->addNote(note, 4, DIVISION_PER_QUARTER);
}

void FileToScore::printFeatures(Plugin::FeatureList *features)
{
    for (Plugin::Feature feature : *features)
    {
        for (float val : feature.values)
        {
            printNote(val, feature.duration, feature.timestamp);

            cout << val << " ";
        }
        if (features->size() > 0)
            cout << endl;
    }
}

