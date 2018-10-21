/*
   vmpt - virtual music power teacher/transcriber

   Copyright (c) 2015 www.dojoy.at, Günther Humer

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Affero General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Affero General Public License for more details.

   You should have received a copy of the GNU Affero General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "generatescore.h"

#include "realtimevamphost.h"
#include "transcribehelper.h"
#include "audioreaderfactory.h"

GenerateScore::GenerateScore()
{
}

GenerateScore::GenerateScore(string outputScore)
  : m_outputScore(outputScore)
{
}

void GenerateScore::fromAudio(std::string inputAudio) {

    m_writer = new MusicWriter();
    m_writer->setFile(this->m_outputScore);
    
    m_writer->start();
    

    auto audioReader = AudioReaderFactory::create(inputAudio);

    // NOTE pyin doesn't work in realtime (uses getRemainingFeatures)
    RealTimeVampHost vampHost("pyin",
                    "pyin", "notes", false,
        *audioReader);

    vampHost.featuresAvailable = std::bind(&GenerateScore::collectFeatures, this, _1);;
    vampHost.process();

    m_writer->finish();

    std::cout << "Score file " << m_outputScore << " written. Have fun!" << std::endl;
}

void GenerateScore::collectFeatures(Plugin::FeatureList *features)
{
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

GenerateScore::~GenerateScore()
{
    if (m_writer)
        delete m_writer;
}

// TODO DoJoY DUPLICATE DEFINITION WITH MXMLWRITER
#define DIVISION_PER_QUARTER 4

void GenerateScore::writeNoteToScore(float val, RealTime duration, RealTime timestamp)
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

    fmxmlDuration += timestamp.sec;//get rid of warning...
    // TODO DoJoY CHECK why?
//    if (mxmlDuration == 0)
//        return;

    // TODO DoJoY timestamp should be used to generate pause.... => last timestamp+duration needed...

    // TODO DoJoY HACK if calculation breaks, you can go back to using quarters only.
    mxmlDuration = DIVISION_PER_QUARTER;

    string note = TranscribeHelper().getNoteFromFreq(val);

    int octave = TranscribeHelper().getOctaveFromFreq(val);
   
	string oct = "";

	if (octave >= 4)
		while ((octave--) >= 4) oct+="'";
	else if (octave < 4)
		while ((octave++) < 4) oct+=",";

    std::cout << "note" << note << std::endl;
    std::cout << "octave" << octave << std::endl;
    std::cout << "duration" << mxmlDuration << std::endl;
    
    
	m_writer->write(note+oct+to_string(mxmlDuration)+ " ");

    /////////m_outputxml->addNote(note, octave, mxmlDuration);
}


