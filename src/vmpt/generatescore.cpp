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

#include  <math.h>



void GenerateScore::writeNoteToScore(float val, RealTime duration, RealTime timestamp)
{
    string note = TranscribeHelper().getNoteFromFreq(val);
    int octave = TranscribeHelper().getOctaveFromFreq(val);
   
	string oct = "";

	if (octave >= 4)
		while ((octave--) >= 4) oct+="'";
	else if (octave < 4)
		while ((octave++) < 4) oct+=",";


	// TODO get from vamp?
    float bpm = 130;
    float durationInBeats = 4/ duration.nsec / (1000.f*1000.f*1000.f) * bpm / 60.f;
    
    string lyDuration = "";
    if (durationInBeats > 16) lyDuration = "\longa";
    if (durationInBeats > 8) lyDuration = "\breve";
    if (durationInBeats > 4) lyDuration = "1";
    if (durationInBeats > 2) lyDuration = "2";
    if (durationInBeats > 1) lyDuration = "4";
    if (durationInBeats > 0.5) lyDuration = "8";
    if (durationInBeats > 0.25) lyDuration = "16";
    
	m_writer->write(note+oct+lyDuration+ " ");
}


