#ifndef TRANSCRIBEHELPER_H
#define TRANSCRIBEHELPER_H

#include <string>

class TranscribeHelper
{
public:
    TranscribeHelper();

    void setStandardPitch(float standardPitch) { m_standardPitch = standardPitch; }

    std::string getNoteFromFreq(float val);

    int getOctaveFromFreq(float frequency);

private:
    std::string getNoteName(int roundedLevel);
    static double log2(double n);

private:
    float m_standardPitch = 440;
};

#endif // TRANSCRIBEHELPER_H
