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
    listNotes.push_back("A");
    listNotes.push_back("A");
    listNotes.push_back("B");
    listNotes.push_back("C");
    listNotes.push_back("C");
    listNotes.push_back("D");
    listNotes.push_back("D");
    listNotes.push_back("E");
    listNotes.push_back("F");
    listNotes.push_back("F");
    listNotes.push_back("G");
    listNotes.push_back("G");

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
