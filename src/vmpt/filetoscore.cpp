#include "filetoscore.h"

#include "realtimevamphost.h"
#include "transcribehelper.h"
#include "audioreaderfactory.h"


#include <QDebug>


SoundFile::SoundFile()
  : m_inputType(UNDEFINED)
{
}

SoundFile::SoundFile(QString soundFileInput)
  : m_soundFileInput(soundFileInput)
  , m_inputType(LOCAL_FILE)
{
}

SoundFile& SoundFile::fromFile(QString soundFileInput)
{
    m_inputType = LOCAL_FILE;
    m_soundFileInput = soundFileInput;

    return *this;
}

void SoundFile::fileToScore(QString mxmlFileOutput)
{
    m_outputxml = new MXMLWriter(mxmlFileOutput.toStdString().c_str());

    auto audioReader = AudioReaderFactory::create(m_soundFileInput);

    // TODOJOY get Plugin info from ?? Settings Class/File
    RealTimeVampHost vampHost("cepstral-pitchtracker",
                    "cepstral-pitchtracker", "notes", false,
        *audioReader);

    vampHost.featuresAvailable = std::bind(&SoundFile::collectFeatures, this, _1);;
    vampHost.process();

    m_outputxml->finish();

    delete m_outputxml;
    m_outputxml = 0;
}

void SoundFile::toMusicXML(QString mxmlFileOutput)
{
    switch(m_inputType)
    {
    case LOCAL_FILE:
        fileToScore(mxmlFileOutput);
        break;
    default:
        throw "Input type not implemented ";
    }
}

void SoundFile::collectFeatures(Plugin::FeatureList *features)
{

    qDebug() << "Features!! ";

    for (Plugin::Feature feature : *features)
    {
        std::cout << std::endl;
        for (float val : feature.values)
        {
            writeNoteToScore(val, feature.duration, feature.timestamp);

            std::cout << val << " ";
        }
        if (feature.values.size() > 0)
            std::cout << std::endl;
    }
}

SoundFile::~SoundFile()
{
    if (m_outputxml)
        delete m_outputxml;
}

// TODOJOY DUPLICATE DEFINITION WITH MXMLWRITER
#define DIVISION_PER_QUARTER 4

void SoundFile::writeNoteToScore(float val, RealTime duration, RealTime timestamp)
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

    mxmlDuration = DIVISION_PER_QUARTER;
    // TODOJOY CHECK why?
//    if (mxmlDuration == 0)
//        return;

    // TODOJOY timestamp should be used to generate pause.... => last timestamp+duration needed...

    QString note = TranscribeHelper().getNoteFromFreq(val);

    int octave = TranscribeHelper().getOctaveFromFreq(val);

    m_outputxml->addNote(note, octave, mxmlDuration);
}


