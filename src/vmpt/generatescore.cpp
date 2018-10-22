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
    

/*
    auto audioReader = AudioReaderFactory::create(inputAudio);
    m_writer->start();      

	std::map<string,float> emptyParams; 
    // NOTE pyin doesn't work in realtime (uses getRemainingFeatures)
    RealTimeVampHost vampHost("pyin",
                    "pyin", "notes", false, emptyParams, 
        *audioReader);


    vampHost.featuresAvailable = std::bind(&GenerateScore::collectFeatures, this, _1);;
    vampHost.process();

    m_writer->finish();
  */
    
    
    m_writer->startChord();
    auto audioReaderChord = AudioReaderFactory::create(inputAudio);
    RealTimeVampHost vampChordHost("nnls-chroma", "chordino", "simplechord", false, std::map<string,float>{{"usehartesyntax", 1.0}}, *audioReaderChord);
    vampChordHost.featuresAvailable = std::bind(&GenerateScore::collectChords, this, _1);
    vampChordHost.process();

	m_writer->finishChord();

    std::cout << "Score file " << m_outputScore << " written. Have fun!" << std::endl;
}

void GenerateScore::collectChords(Plugin::FeatureList * features) {
   for (Plugin::Feature feature : *features)
    {
		writeChordToScore(feature.label, feature.timestamp);

        std::cout << std::endl;
        for (float val : feature.values)
        {
            writeChordToScore(feature.label, feature.timestamp);
        }
        if (feature.values.size() > 0)
            std::cout << std::endl;
    }
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
#include <string.h>

vector<string> getScale(string strTonic, bool isMinor=false) {
    char notes[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    int notesDistance[] = {2,1,2,2,1,2,2};

    int notesDistanceMajor[] = {2,2,1,2,2,2,1};
    int *notesDistanceMinor = notesDistance;

    int accModifier = 0;
    if (strTonic.length() != 1)
        if (strTonic.substr(1, strTonic.length()-1) == "is")
            accModifier = -1;
        else if (strTonic.substr(1, strTonic.length()-1) == "es")
            accModifier = +1;

    int tonicIndex=0;
    for (int i = 0; i < 8; ++i) {
        if (notes[i] == strTonic[0]) {
            tonicIndex = i;
            break;
        }

    }

    vector<string> res;

    for (int i = 0; i < 8; ++i) {
        int noteIndex = (i+tonicIndex)%7;
        string note = "" + notes[noteIndex];

        int dist = accModifier;
        int correctDistance = 0;
        for (size_t d = 0; d <= i; ++d) {
            dist += notesDistance[(tonicIndex + d)%7];
            if (isMinor)
                correctDistance += notesDistanceMinor[d];
            else
                correctDistance += notesDistanceMajor[d];

        }
        if (correctDistance - dist == 1)
            note += "is";
        else if  (correctDistance - dist == -1)
            note += "es";

        res.push_back(note);
    }

    return res;

}
string calcBass(string strBass, string strTonic, bool isMinor=false) {
    string bassModifier = "";
    int bassIndex = 0;


    if (strBass.length() == 2) {
        int bassIndex = int(strBass[1]) - 1;

        if (strBass[0] == 'b')
            bassModifier = "es";
        else if (strBass[0] == '#')
            bassModifier = "is";
    }else
        bassIndex = int(strBass[0]) - 1;


    string bass = getScale(strTonic, isMinor) [bassIndex];

    if (bass.length() > 1 && bassModifier != "")
        if (bass.substr(1, bass.length() -1) == "is" && bassModifier == "es" or bass.substr(1, bass.length() -1) == "es" and bassModifier == "is")
            bass = bass[0];
        else
            bass += bassModifier;

    return bass;
}

#include <string>
#include <locale>
#include <iostream>       // std::cout
#include <string>         // std::string
#include <locale>
#include <algorithm>

string GenerateScore::getLyChordFromHarte(string chord, RealTime timestamp) {

    string result = "";
    // HACK TODO
//    int duration = getDurationFromTimestamp();
    int duration = 4;

    if (chord == "N") {
        result = "r" + duration;
        return result;
    }

    std::transform(chord.begin(), chord.end(), chord.begin(), ::tolower);

    if (chord.length() < 2)
        return chord + to_string(duration);

    //BASE + DURATION + ifmodifier : modifier + ifbass /bass


    //// BASE

    string base = chord.substr(0, 1);

    int position = 1;

    if (chord[1] == 'b') {
        base += "es";
        position++;
    }else if (chord[1] == '#') {
        base += "is";
        position++;
    }

    //// BASE

    int basspos = chord.find('/');

    size_t posendmod;

    if (basspos !=-1) posendmod = basspos ;
    else posendmod = chord.length();



    string modifier = chord.substr(position, posendmod);

    if (modifier != "" && modifier[0] != ':')
        modifier = ':' + modifier;

    modifier = modifier.replace(modifier.begin(), modifier.end(), 'hdim7', '7.5-');



        string bass = "";
        /*
        if (basspos != -1) {
            bass = chord.substr(basspos + 1,chord.length());
            bass = calcBass(bass, base, chord[1] == 'm');
        }
        if (bass != "")
            bass = '/' + bass;
*/
        return base+to_string(duration) + modifier + bass;
}


void GenerateScore::writeChordToScore(string chord, Vamp::RealTime timestamp) {
    string res = getLyChordFromHarte(chord, timestamp);
    m_writer->write(res);
}

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
    if (durationInBeats > 16) lyDuration = "\\longa";
    if (durationInBeats > 8) lyDuration = "\\breve";
    if (durationInBeats > 4) lyDuration = "1";
    if (durationInBeats > 2) lyDuration = "2";
    if (durationInBeats > 1) lyDuration = "4";
    if (durationInBeats > 0.5) lyDuration = "8";
    if (durationInBeats > 0.25) lyDuration = "16";
    
	m_writer->write(note+oct+lyDuration+ " ");
}


