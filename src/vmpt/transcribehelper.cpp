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

#include "transcribehelper.h"

#include <cassert>
#include <math.h>
#include <vector>

using std::vector;
using std::string;

TranscribeHelper::TranscribeHelper()
{

}

double TranscribeHelper::log2(double n)
{
    return log(n) / log(2);
}

std::string TranscribeHelper::getNoteName(int roundedLevel)
{
    // level ranges from A=440(e.g.) up and down. every step is a half tone...
    // TODO Alterations: generate both in one function/class, where the key is stored

    vector<string> listNotes;
    listNotes.push_back("a");
    listNotes.push_back("ais");
    listNotes.push_back("b");
    listNotes.push_back("c");
    listNotes.push_back("cis");
    listNotes.push_back("d");
    listNotes.push_back("dis");
    listNotes.push_back("e");
    listNotes.push_back("f");
    listNotes.push_back("fis");
    listNotes.push_back("g");
    listNotes.push_back("gis");

    int realLevel = roundedLevel % 12;

    if (realLevel < 0) realLevel += 12;

    return listNotes[realLevel];
}

std::string TranscribeHelper::getNoteFromFreq(float val)
{
    /**
     * freq = 440 * 2 ^ i/12
     * 12 * log2(freq/440) = level
     * */

    double level = 12 * log2(val/440.);
    int roundedLevel = round(level);

    string noteName = getNoteName(roundedLevel);

    return noteName;
}

int TranscribeHelper::getOctaveFromFreq(float frequency)
{
    int octaveOfStandardPitch = 4; // octave of standard pitch (a)

    /**
     * 440 * 2 ^(noteDistanceFromA/12) = frequence
     * */
    double c4freq = 440 * pow(2, -9.5/12.);

    if (frequency < c4freq)
    {
        do
        {
            octaveOfStandardPitch--;
            frequency *= 2.;
        } while (frequency < c4freq);

        return octaveOfStandardPitch;
    }


    while (frequency > c4freq)
    {
        octaveOfStandardPitch++;
        frequency /= 2.;
    }
    octaveOfStandardPitch--;

    return octaveOfStandardPitch;
}

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

#include <iostream>
#include <string>

using std::to_string;

string TranscribeHelper::getLyChordFromHarte(string chord, Vamp::RealTime timestamp) {

    string result = "";
    // HACK TODO

    vector<string> durations = getLyDurationFromRealtime(timestamp);
    assert(!durations.empty());

    string duration = durations.at(0);

    if (chord == "N") {
        result = "r" + duration;
        return result;
    }

    std::transform(chord.begin(), chord.end(), chord.begin(), ::tolower);

    if (chord.length() < 2)
        return chord + duration;

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

    if (modifier != "" && modifier[0] != ':') {
        modifier = ':' + modifier;

        modifier = modifier.replace(modifier.begin(), modifier.end(), 'hdim7', '7.5-');
    }



        string bass = "";

        if (basspos != -1) {
            bass = chord.substr(basspos + 1,chord.length());
            bass = calcBass(bass, base, chord[1] == 'm');
        }
        if (bass != "")
            bass = '/' + bass;

        result =  base+duration + modifier + bass;

        return result;
}

std::vector<std::string> TranscribeHelper::getLyDurationFromRealtime(Vamp::RealTime rtDuration) {
    std::vector<std::string> result;
    float quarterInSeconds = 60.f/this->m_bpm;

    // smallest note 128th
    int x = 128;
    float xInSeconds = 4.f * quarterInSeconds / 128.;
    while(x >=1) {
        if (rtDuration.nsec <= xInSeconds * (1000.f * 1000.f * 1000.f))
            result.push_back(to_string(x));

        x = x / 2;
        xInSeconds = xInSeconds * 2;
    }

    if (result.empty())
        result.push_back(to_string(4));

    return result;
}
