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
