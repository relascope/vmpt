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

#ifndef TRANSCRIBEHELPER_H
#define TRANSCRIBEHELPER_H

#include <string>


#include <vamp-hostsdk/RealTime.h>

using std::string;
#include <vamp-hostsdk/RealTime.h>

class TranscribeHelper
{
public:
    TranscribeHelper();

    void setStandardPitch(float standardPitch) { m_standardPitch = standardPitch; }

    std::string getNoteFromFreq(float val);

    int getOctaveFromFreq(float frequency);

    string getLyChordFromHarte(string chord, Vamp::RealTime timestamp);

private:
    std::string getNoteName(int roundedLevel);
    static double log2(double n);

private:
    float m_standardPitch = 440;
};

#endif // TRANSCRIBEHELPER_H
